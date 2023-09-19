import re


def strip_heredoc(heredoc):
    return re.sub(r"\s+", " ", heredoc).strip()
