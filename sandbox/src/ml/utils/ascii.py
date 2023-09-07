BOLD = "\033[1m"
CYAN = "\033[36m"
GREEN = "\033[32m"
MAGENTA = "\033[35m"
NORMAL = "\033[10m"
NO_UNDERLINE = "\033[24m"
RED = "\033[31m"
RESET = "\033[0m"
UNDERLINE = "\033[4m"
YELLOW = "\033[33m"


def puts(msg, *fmts, begin="\n", end=RESET, print_end="\n"):
    fmt_chain = f"{BOLD}"

    for fmt in fmts:
        fmt_chain += fmt

    print(begin + fmt_chain + msg + end, end=print_end)
