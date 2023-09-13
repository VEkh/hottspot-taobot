def seconds_to_clock(duration):
    hours = int(duration / (60 * 60))
    minutes = int((duration % (60 * 60)) / 60)
    seconds = int(duration % 60)

    f_hours = str(hours).zfill(2)
    f_minutes = str(minutes).zfill(2)
    f_seconds = str(seconds).zfill(2)

    out = f"{f_minutes}:{f_seconds}"

    if hours:
        out = f"{f_hours}:{out}"

    return out
