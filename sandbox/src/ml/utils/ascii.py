BOLD = "\033[1m"
CYAN = "\033[36m"
GREEN = "\033[32m"
NORMAL = "\033[10m"
RED = "\033[31m"
RESET = "\033[0m"
UNDERLINE = "\033[4m"
YELLOW = "\033[33m"


def puts(msg, *fmts):
    fmt_chain = f"{BOLD}"

    for fmt in fmts:
        fmt_chain += fmt

    print(fmt_chain + msg + RESET)
