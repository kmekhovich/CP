# ifdef __WIN32__
int getchar_unlocked () {
return _getchar_nolock ();
}
void putchar_unlocked ( char c) {
_putchar_nolock ( c );
}
# endif
int64_t getInt () {
    char c = '\0';
    while (c <= ' ') {
        c = getchar_unlocked ();
    }
    int64_t sign = +1;
    if (c == '+' || c == '-') {
        sign = (c == '+') ? +1 : -1;
        c = getchar_unlocked ();
    }
    uint64_t res = 0;
    while ('0' <= c && c <='9') {
        res = ( res << 3) + ( res << 1);
        res += c - '0';
        c = getchar_unlocked ();
    }
    return res * sign ;
}
