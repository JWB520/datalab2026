/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x&~y)&~(x&y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x)
    {
        if(!y)return 1;
        return 0;
    }
    if(!y)return 0;
    return !((x&0x80000000)^(y&0x80000000));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
/*
 * logtwo - floor(log2(v)), v > 0
 * Legal ops: > < >> << |   Max ops: 23
 */
int logtwo(int v)
{
    int r, b;//r代表的是已经确定的最高位的偏移，b代表的是二分步骤是向左还是原地不动

    r = 0;

    b = (v >> 16) > 0;//最高位是在前16位还是后16位
    r = r | (b << 4); //执行偏移

    b = (v >> (r | 8)) > 0;//注意到v大于0，这里判断的是在当前划定的16位中是在前8位还是后8位
    r = r | (b << 3);//执行偏移

    b = (v >> (r | 4)) > 0;
    r = r | (b << 2);

    b = (v >> (r | 2)) > 0;
    r = r | (b << 1);

    r = r | ((v >> (r | 1)) > 0);//直到判断到一位为止

    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    n=n<<3,m=m<<3;
    int s1=0x000000ff<<n,s2=0x000000ff<<m;
    int t1=(((x&s1)>>n)<<m)&s2,t2=(((x&s2)>>m)<<n)&s1;
    return (x&~(s1|s2))|t1|t2;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned ans=0,mark1=1,mark2=0x80000000;
    while(mark2)
    {
        int x=0;
        x=v&mark1;//提取出需要翻转的那一位是0还是1；
        x=!!x;//将这一位映射到最低位
        x=~x+1;//将这个最低位铺满所有位
        x=x&mark2;//将这个最低位映射到需要翻转的目的那一位上
        ans=ans|x;//将这个目的位的值放到结果中
        mark1=mark1<<1;//挪动指针
        mark2=mark2>>1;
    }
    return ans;
}
// unsigned reverse(unsigned v) {
//     v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
//     v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
//     v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
//     v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
//     v = (v >> 16) | (v << 16);
//     return v;
// }

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mov=0x80000000;//这里之所以要写成这样，是因为直接用0x~会默认为无符号数
    int s=~((mov>>n)<<1);//人造一个前n-1位为0的掩码
    return (x>>n)&s;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int x1=~x;//只需要数清楚x1左侧有多少个0，后面采用二分的方式来实现
    int mark=0xffff0000;
    int ans=0;
    int b=0;//记录当前这部分是否有1
    b=!!(mark&x1);
    ans=ans+(b<<4);
    mark=(mark>>8)<<(b<<4);

    b=!!(mark&x1);
    ans=ans+(b<<3);
    mark=(mark>>4)<<(b<<3);

    b=!!(mark&x1);
    ans=ans+(b<<2);
    mark=(mark>>2)<<(b<<2);

    b=!!(mark&x1);
    ans=ans+(b<<1);
    mark=(mark>>1)<<(b<<1);

    b=!!(mark&x1);
    ans=ans+b;

    return 32+~ans+!(x1);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
int float_i2f(int x) {
    int sign;  //这里记录的是符号位
    int ux;    //这个数用来存储x绝对值的二进制表示
    int mant;  //这里记录的是规格化的尾数，它的最高位是1，后面跟着23位的尾数
    int frac;  //规格化尾数中的小数部分
    int rem;   //四舍五入被丢弃的低8位
    int e;     //指数

    if (x == 0)//特判0
        return 0;

    sign = x & (1 << 31);
    ux = x;
    if (x < 0)
        ux = -ux;//x的绝对值

    e = 31;
    mant = ux;
    while (mant > 0) {//把规格化的尾数移到最高位
        mant = mant << 1;
        e = e - 1;
    }

    frac = (mant >> 8) & 0x7FFFFF;//提取小数部分
    rem = mant & 0xFF;//提取被丢弃的低8位

    if (rem + (frac & 1) > 0x80)   //向偶数位进位
        frac = frac + 1;

    if (frac == 0x800000) {//如果进位导致指数发生变化，处理这种边界
        frac = 0;
        e = e + 1;
    }

    return sign | ((e + 127) << 23) | frac;//合成答案
}


/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xff;
    unsigned frac = uf & 0x7fffff;

    if (exp == 0xff) return uf;
    if (exp == 0) return sign | (frac << 1);
    exp++;
    if (exp == 0xff) return sign | (exp << 23);
    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7ff;
    unsigned frac_hi = uf2 & 0xfffff;
    unsigned exponent, significand_hi, magnitude;

    if (exp < 1023)                 /* 0、denorm、|f|<1：向零取整为 0 */
        return 0;

    exponent = exp - 1023;          /* 到这里 exp>=1023，无回绕 */

    if (exponent >= 31)             /* |f|>=2^31 溢出；Inf/NaN(=1024) 也落在这 */
        return 0x80000000;

    significand_hi = 0x100000 | frac_hi;      /* 补上隐含的 1，21 位 */

    if (exponent <= 20)
        magnitude = significand_hi >> (20 - exponent);
    else
        magnitude = (significand_hi << (exponent - 20)) | (uf1 >> (52 - exponent));

    if (sign)
        return ~magnitude + 1;      /* 取负：不用强转、不用一元负号 */
    return magnitude;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) return 0;
    if (x < -126) return 1 << (x + 149);   /* denorm：第 x+149 位上是 1 */
    if (x > 127)  return 0x7f800000;       /* +INF */
    return (x + 127) << 23;                /* norm：阶码字段 = x + 127 */
}

