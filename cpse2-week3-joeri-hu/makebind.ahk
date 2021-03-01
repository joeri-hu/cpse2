#singleinstance
#persistent
#noenv

#z:: run_make(,, "confirm")
#+z:: run_make(, "max", "confirm", "limit")
#^z:: run_make(,, "confirm", "rebuild")
#^+z:: run_make(, "max", "confirm", "rebuild", "limit")

run_make(script := "makerun.cmd", window_size := "", options*) {
    bullet_symbol := Chr(0x2022)
    save_active_file(bullet_symbol)
    static pid
    WinClose, % "ahk_pid" . pid
    Run, % script . " " . join(, options*), % A_ScriptDir, % window_size, pid
}

save_active_file(editor_title, editor_class := "PX_WINDOW_CLASS") {
    if (WinActive(A_ScriptDir . "ahk_class" . editor_class)) {
        WinGetTitle, title, A

        if (InStr(title, editor_title)) {
            SendInput, ^{s}
        }
    }
}

join(delim := " ", args*) {
    for key, value in args {
        result .= delim . value
    }
    return SubStr(result, StrLen(delim) + 1)
}
