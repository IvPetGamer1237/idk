 if [[ $(date +%m%d) == 0401 ]]; then
    emacs() {
        if [[ $1 == "-nw" ]]
        then
            (( RANDOM % 2 )) && /usr/bin/vim "$2" || /usr/bin/emacs -nw "$2"
        else
            (( RANDOM % 2 )) && /usr/bin/gvim "$@" || /usr/bin/emacs "$@"
        fi
    }
    vim() {
        (( RANDOM % 2 )) && /usr/bin/emacs -nw "$@" || /usr/bin/vim "$@"
    }
    gvim() {
        (( RANDOM % 2 )) && /usr/bin/emacs "$@" || /usr/bin/gvim "$@"
    }
fi 
