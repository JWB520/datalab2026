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
    int s=~(((x&0x80000000)>>n)<<1);//人造一个前n-1位为0的掩码
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
    mark=(mark>>8)<<(b<<3);

    b=!!(mark&x1);
    ans=ans+(b<<2);
    mark=(mark>>8)<<(b<<2);

    b=!!(mark&x1);
    ans=ans+(b<<1);
    mark=(mark>>8)<<(b<<1);

    b=!!(mark&x1);
    ans=ans+b;

    return 32+~ans+1;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int i) {
    unsigned sign = i >> 31;          // 提取符号位
    unsigned u = (unsigned)i;

    if (i == 0) return 0;             // 特判 0
    if (i == 0x80000000) {            // 特判 INT_MIN（-2^31 取反会溢出）
        return (1u << 31) | (158u << 23);
    }

    // 取绝对值
    if (sign) u = ~u + 1;

    // 找最高位1的位置
    int pos = 31;
    while (!(u & (1u << pos))) pos--;

    // 计算指数（偏置值127 + 实际指数pos）
    unsigned exp = 127 + pos;

    // 把最高位1左移到第31位，方便后面统一处理尾数
    u <<= (31 - pos);

    // 现在 u 的第31位是隐含的1，第30~8位是尾数的前23位，第7~0位是要丢弃的低位
    unsigned frac = (u >> 8) & 0x7fffff;  // 取23位尾数
    unsigned dropped = u & 0xff;          // 被丢弃的8位

    // 向偶数舍入（round to even）
    if (dropped > 0x80) {                 // 大于一半，向上舍入
        frac++;
    } else if (dropped == 0x80) {         // 恰好一半，向偶数舍入
        if (frac & 1) frac++;             // 尾数最低位是1就+1变偶数
    }

    // 舍入后可能进位导致尾数溢出到指数
    if (frac >> 23) {
        exp++;
        frac &= 0x7fffff;
    }

    return (sign << 31) | (exp << 23) | frac;
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
    unsigned exponent;
    unsigned significand_hi;
    unsigned magnitude;

    if (exp == 0x7ff) return 0x80000000u;
    exponent = exp - 1023;
    if (exp < 1023) return 0;
    if (exponent > 31) return 0x80000000u;
    if (exponent == 31) {
        if (sign && frac_hi == 0 && uf1 == 0) return 0x80000000u;
        return 0x80000000u;
    }

    significand_hi = 0x100000 | frac_hi;
    if (exponent <= 20) {
        magnitude = significand_hi >> (20 - exponent);
    } else {
        unsigned shift = 52 - exponent;
        magnitude = (significand_hi << (32 - shift)) | (uf1 >> shift);
    }
    if (sign) return -((int)magnitude);
    return (int)magnitude;
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
    if (x < -126) return 1u << (x + 149);
    if (x > 127) return 0x7f800000;
    return (unsigned)(x + 127) << 23;
}
