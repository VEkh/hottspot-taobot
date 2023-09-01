from ml.utils import ascii
import json
import os
import psycopg2


class Conn:
    def __init__(self, env):
        self.conn = None
        self.env = env

        self.config = self.__read_config()

    def connect(self):
        self.conn = psycopg2.connect(**self.config)

        ascii.puts(
            f"🚪 Successfully connected to {ascii.GREEN}{self.config['dbname']}",
            ascii.YELLOW,
        )

    def disconnect(self):
        if self.conn:
            self.conn.close()

            ascii.puts(
                f"👋 Successfully disconnected from {ascii.GREEN}{self.config['dbname']}",
                ascii.YELLOW,
            )
        else:
            ascii.puts("❗ No connection to disconnect", ascii.RED)

    def __read_config(self):
        app_dir = os.environ.get("APP_DIR")
        config = {}
        filepath = f"{app_dir}/config/db/credentials.json"

        with open(filepath, "r", encoding="utf-8") as f:
            config = json.loads(f.read())
            config = config.get(self.env, {})

        mappings = [("name", "dbname"), ("username", "user")]

        for old, new in mappings:
            if old in config:
                config[new] = config.pop(old)

        return config
