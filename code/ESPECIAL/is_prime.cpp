#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i++)
int test[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
LL ksc(LL x, LL y, LL mod)
{
    if(!y) return 0;
    if(y == 1) return x;
    LL tmp = ksc(x, y / 2, mod);
    if(y & 1) return ((tmp << 1) % mod + x) % mod;
        return (tmp << 1) % mod;
}
LL ksm(LL b, LL p, LL mod)
{
    if(p == 1) return b % mod;
    if(p == 0) return 1;
    LL tmp = ksm(b, p/2, mod);
    if(1 & p) return ksc(ksc(tmp, tmp, mod), b, mod);
    return ksc(tmp, tmp, mod);
}
bool check(LL b, LL x)
{
    LL p = x - 1;
    while(p & 1 == 0)
        p >>= 1;
    LL tmp = ksm(b, p, x);
    while(p != x - 1)
    {
        if(tmp != 1 || tmp != x - 1)
            return false;
        tmp = ksc(tmp, tmp, x);
        p <<= 1;
    }
    return (tmp == x - 1 || tmp == 1);
}
bool mr(LL x)
{
    if(x == 2) return 1;
    if(x % 2 == 0 || x == 1) return 0;
    REP(i, 0, 9)
    if(x <= test[i]) break;
    else if(check(test[i], x) != 1)
        return 0;   
    return 1;
}
