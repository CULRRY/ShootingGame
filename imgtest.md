![image-20230830012954141](https://i.imgur.com/69xvAaD.png)

```assembly
mov ebp, h0CC
```

```c
int a;
int b;
int c;

a = 1;
b = 2;
c = a + b;
c = a * 3;
```





### CPU의 레지스터

굉장히 많은 레지스터들이 존재하지만, 그중 일부 주요 부분만 기술

- ebp : 현 스택 프레임의 시작 주소.
- esp : 현 스택의 포인터. (자료구조 Stack의 top을 생각하면 된다.)
- eax : 산술, 논리 연상에 사용하는 레지스터.
- ecx : 반복문 들의 카운팅을 위한 레지스터.
- esi : 데이터 복사 시 원본 주소.
- edi : 데이터 복사 시 목적지 주소.

※ 32bit 기준

bp를 예로들면

I————————I 64bit (rbp)

I————I     32bit (ebp)

I——I       16bit (bp)