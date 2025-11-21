"""
Greedy Backward Feature Elimination

Systematically removes features one at a time to find optimal feature subset
that maximizes profit loss capture performance.
"""

from .trainer import Trainer
from pathlib import Path
from tabulate import tabulate
import json
import ml.utils as u
import numpy as np
import os
import pandas as pd


class FeatureEliminator:
    def __init__(
        self,
        training_data_builder,
        optimization_metric="profit_loss_capture",  # or 'accuracy'
    ):
        self.baseline_performance = None
        self.elimination_history = []
        self.feature_removed = []
        self.optimization_metric = optimization_metric
        self.training_data_builder = training_data_builder

    def run(self, max_iterations=None):
        u.ascii.puts(f"{'='*60}", u.ascii.CYAN, print_end="")
        u.ascii.puts(
            "🚀 Starting Greedy Backward Feature Elimination",
            u.ascii.CYAN,
            print_end="",
        )
        u.ascii.puts(f"{'='*60}", u.ascii.CYAN)

        current_performance = self._get_baseline_performance()
        current_features = current_performance["features_remaining"].copy()

        iteration = 0

        while True:
            iteration += 1

            if max_iterations and iteration > max_iterations:
                u.ascii.puts(
                    f"🍾  Reached max iterations ({max_iterations})", u.ascii.YELLOW
                )
                break

            u.ascii.puts(f"{'='*60}", u.ascii.MAGENTA, print_end="")
            u.ascii.puts(
                f"ITERATION {iteration}: {len(current_features)} features remaining",
                u.ascii.MAGENTA,
                print_end="",
            )
            u.ascii.puts(f"{'='*60}", u.ascii.MAGENTA)

            candidates = self._find_best_feature_to_remove(
                current_features=current_features,
                current_performance=current_performance,
            )

            best_candidate = candidates[0]

            if best_candidate["improvement"] <= 0:
                u.ascii.puts(
                    f"🛑 No improvement from removing any feature",
                    u.ascii.RED,
                    print_end="",
                )

                u.ascii.puts(
                    f"   Best Candidate: {best_candidate['feature_removed']}",
                    u.ascii.RED,
                    print_end="",
                )

                u.ascii.puts(
                    f"   Would change {self.optimization_metric} by: {best_candidate['improvement']:+.3f}",
                    u.ascii.RED,
                    print_end="",
                )

                u.ascii.puts(f"🎉 Feature elimination complete!", u.ascii.GREEN)

                break

            feature_to_remove = best_candidate["feature_removed"]
            current_features.remove(feature_to_remove)

            self.features_removed = self.elimination_history[-1]["features_removed"] + [
                feature_to_remove
            ]

            current_performance = {
                "iteration": iteration,
                "features_removed": self.features_removed,
                "features_remaining": current_features.copy(),
                "n_features": len(current_features),
                "mean_accuracy": best_candidate["mean_accuracy"],
                "std_accuracy": best_candidate["std_accuracy"],
                "mean_profit_loss_capture": best_candidate["mean_profit_loss_capture"],
                "std_profit_loss_capture": best_candidate["std_profit_loss_capture"],
                "mean_confidence": best_candidate["mean_confidence"],
            }

            self.elimination_history.append(current_performance)

            u.ascii.puts(
                f"🎯 REMOVED: {feature_to_remove}", u.ascii.GREEN, print_end=""
            )
            u.ascii.puts(
                f"   New {self.optimization_metric}: {current_performance[f'mean_{self.optimization_metric}']:.3f}",
                u.ascii.GREEN,
            )
            u.ascii.puts(
                f"   Improvement: {best_candidate['improvement']:+.3f}", u.ascii.GREEN
            )

        self._print_summary()

        return self.elimination_history

    def _evaluate_without_feature(self, feature_to_remove, previously_removed):
        trainer = Trainer(
            excluded_features=previously_removed + [feature_to_remove],
            training_data_builder=self.training_data_builder,
        )

        results = trainer.train_with_cv()
        cv = results["cv"]

        return {
            "feature_removed": feature_to_remove,
            "mean_accuracy": cv["accuracy"].mean(),
            "std_accuracy": cv["accuracy"].std(),
            "mean_profit_loss_capture": cv["profit_loss_capture"].mean(),
            "std_profit_loss_capture": cv["profit_loss_capture"].std(),
            "mean_confidence": cv["mean_confidence"].mean(),
        }

    def _find_best_feature_to_remove(self, current_features, current_performance):
        u.ascii.puts(
            f"🔍 Testing removal of {len(current_features)} features...",
            u.ascii.YELLOW,
        )

        removal_candidates = []
        previously_removed = current_performance["features_removed"]

        for idx, feature in enumerate(current_features, 1):
            u.ascii.puts(
                f"  [{idx}/{len(current_features)}] Testing removal of: {feature}",
                u.ascii.CYAN,
            )

            eval_result = self._evaluate_without_feature(
                feature_to_remove=feature,
                previously_removed=previously_removed,
            )

            improvement = (
                eval_result[f"mean_{self.optimization_metric}"]
                - current_performance[f"mean_{self.optimization_metric}"]
            )

            eval_result["improvement"] = improvement
            removal_candidates.append(eval_result)

            u.ascii.puts(
                f"      {self.optimization_metric}: {eval_result[f'mean_{self.optimization_metric}']:+.3f} (change: {improvement:+.3f})",
                u.ascii.MAGENTA,
            )

        removal_candidates.sort(key=lambda x: x["improvement"], reverse=True)

        return removal_candidates

    def _get_baseline_performance(self):
        u.ascii.puts(f"{'='*60}", u.ascii.CYAN, print_end="")
        u.ascii.puts("📊 BASELINE: Training with ALL Features", u.ascii.CYAN)
        u.ascii.puts(f"{'='*60}", u.ascii.CYAN)

        trainer = Trainer(
            excluded_features=[],
            training_data_builder=self.training_data_builder,
        )

        results = trainer.train_with_cv()
        cv = results["cv"]

        features_remaining = self.training_data_builder.feature_columns.copy()

        baseline = {
            "iteration": 0,
            "features_removed": [],
            "features_remaining": features_remaining,
            "n_features": len(features_remaining),
            "mean_accuracy": cv["accuracy"].mean(),
            "std_accuracy": cv["accuracy"].std(),
            "mean_profit_loss_capture": cv["profit_loss_capture"].mean(),
            "std_profit_loss_capture": cv["profit_loss_capture"].std(),
            "mean_confidence": cv["mean_confidence"].mean(),
        }

        self.baseline_performance = baseline
        self.elimination_history.append(baseline)

        u.ascii.puts(
            f"📊 Baseline {self.optimization_metric}: {baseline[f'mean_{self.optimization_metric}']:.3f}",
            u.ascii.GREEN,
        )

        return baseline

    def _print_summary(self):
        u.ascii.puts(f"{'='*60}", u.ascii.CYAN, print_end="")
        u.ascii.puts("📊 FEATURE ELIMINATION SUMMARY", u.ascii.CYAN, print_end="")
        u.ascii.puts(f"{'='*60}", u.ascii.CYAN)

        summary_data = []

        for entry in self.elimination_history:
            summary_data.append(
                {
                    "iteration": entry["iteration"],
                    "n_features": entry["n_features"],
                    "accuracy": f"{entry['mean_accuracy']:.3f} (±{entry['std_accuracy']:.3f})",
                    "profit_loss_capture": f"{entry['mean_profit_loss_capture']:+.3f} (±{entry['std_profit_loss_capture']:.3f})",
                    "confidence": f"{entry['mean_confidence']:.3f}",
                }
            )

        u.ascii.puts(
            tabulate(summary_data, headers="keys", tablefmt="psql"),
            u.ascii.MAGENTA,
        )

        best_idx = max(
            range(len(self.elimination_history)),
            key=lambda i: self.elimination_history[i][
                f"mean_{self.optimization_metric}"
            ],
        )

        best_config = self.elimination_history[best_idx]
        self.best_config = best_config

        u.ascii.puts(f"🏆 BEST CONFIGURATION:", u.ascii.GREEN, print_end="")
        u.ascii.puts(
            f"   Iteration: {best_config['iteration']}", u.ascii.GREEN, print_end=""
        )
        u.ascii.puts(
            f"   Features: {best_config['n_features']}", u.ascii.GREEN, print_end=""
        )
        u.ascii.puts(
            f"   Accuracy: {best_config['mean_accuracy']:.1%} (±{best_config['std_accuracy']:.1%})",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(
            f"   P&L Capture: {best_config['mean_profit_loss_capture']:+.1%} (±{best_config['std_profit_loss_capture']:.1%})",
            u.ascii.GREEN,
            print_end="",
        )
        u.ascii.puts(
            f"   Confidence: {best_config['mean_confidence']:.3f}",
            u.ascii.GREEN,
        )

        if best_config["iteration"] > 0:
            u.ascii.puts(
                f"   Features Removed: {best_config['features_removed']}",
                u.ascii.YELLOW,
            )

        u.ascii.puts(
            f"   Features Remaining ({len(best_config['features_remaining'])}):",
            u.ascii.CYAN,
            print_end="",
        )

        for feature in sorted(best_config["features_remaining"]):
            u.ascii.puts(f"     - {feature}", u.ascii.CYAN)

        current_dir = Path(__file__).resolve().parent
        save_dir = os.path.join(current_dir, "feature_selection")
        os.makedirs(save_dir, exist_ok=True)

        save_path = os.path.join(
            save_dir,
            f"greedy_backward_feature_elimination_{self.training_data_builder.symbol}.json",
        )

        with open(save_path, "w") as f:
            json.dump(best_config, f, indent=2, default=str)

        return best_config
