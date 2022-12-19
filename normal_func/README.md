在一个.cpp与.h的文件中实现这些功能



实现memcpy函数的功能

memcpy指的是C和C++使用的内存拷贝函数，函数原型为void *memcpy(void *destin, void *source, unsigned n)；函数的功能是从源内存地址的起始位置开始拷贝若干个字节到目标内存地址中，即从源source中拷贝n个字节到目标destin中。

参考链接：https://www.iculture.cc/forum-post/28561.html

```cpp
void* memmv(void* dst, const void* src, int count)
{
    void* ret = dst;
    if (dst <= src || (char*)dst >= ((char*)src + count)) {
        while (count--) {
            *(char*)dst = *(char*)src;
            dst = (char*)dst + 1;
            src = (char*)src + 1;
        }
    }
    else {
        dst = (char*)dst + count - 1;
        src = (char*)src + count - 1;
        while (count--) {
            *(char*)dst = *(char*)src;
            dst = (char*)dst - 1;
            src = (char*)src - 1;
        }
    }
    return(ret);
}
```



