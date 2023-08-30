---
title: Stack의 어셈블리 분석
date: "2023-07-12"
modified: "2023-08-30"
---

## Assembly

- C로 프로그래밍을 한 뒤에 컴파일 과정을 거치면, C 컴파일러가 C 소스코드를 CPU가 인식하는 기계어로 변환한다.

```C
int a;
int b;
int c;

a = 1;
b = 2;
c = a + b;
c = a * 3;
```

위와 같은 C 코드가 있을 때, 이를 어셈블리로 보면 아래와 같다.

```assembly
push        ebp
mov         ebp, esp
sub         esp, 0E4h

push        ebx
push        esi
push        edi

lea         edi, [ebp-0E4h]
mov         ecx, 39h
mov         eax, 0CCCCCCCCh
rep stos    dword ptr es: [edi]

mov         dword ptr [a], 1
mov         dword ptr [b], 2
mov         eax, dword ptr [a]
add         eax, dword ptr [b]
mov         dword ptr [c], eax
imul        eax, dword ptr [a], 3
mov         dword ptr [c], eax
```

> ※ 이런 식으로 프로그래밍을 할 일은 없고, 코드를 보고 기계어로는 어떻게 동작할지 떠오를 수준만 되면 됨.

- 기본적으로 모든 프로그램의 처리는 스택 메모리에 저장되며, 위의 C 코드처럼 변수를 선언하여 사용할 때, **변수 메모리가 할당되는 개념은 단순히 스택의 일부 영역을 비워두고 그 공간을 사용하는 개념**이다.

  > ***PLUS.*** 일반적으로 프로세스 당 스택의 크기는 1MB이다. [[/STACK msdn 문서]](https://learn.microsoft.com/ko-kr/cpp/build/reference/stack-stack-allocations?view=msvc-170)

- 우리가 a, b, c라고 붙힌 변수의 이름은 C 코드 상의 이름이지, 어셈블리에서는 그냥 ebp기준으로 상대주소로 계산한다.

  ```assembly
  mov         dword ptr [ebp-8], 1
  mov         dword ptr [ebp-14h], 2
  
  *여기서 h는 16진수를 표현할 때 사용함. 0x14와 같은 의미이다.
  ```

  > ***PLUS.*** 4바이트인 int를 저장하는데 ebp를 8, 20씩 빼는 이유는 debug build 이기 때문이다. 디버깅 모드에서는 다른 메모리의 침범을 막고 확인하기 위한 용도로서 변수 사이에 4바이트씩 padding을 넣는다.
  >
  > ```
  > | 4byte |   a   | 4byte |   b   | 4byte |
  > ↑ [ebp]         ↑ [ebp - 8]     ↑ [ebp - 20]
  > ```



- 즉, a라는 변수를 선언하면 그냥 메모리의 일정 부분을 비워두게 되고, 컴파일러가 a라는 변수를 실제로 사용할 떈, bp를 기준으로 어느 위치의 메모리를 사용하는지 실제 주소를 반환한다.

  >***PLUS.*** 따라서 지역변수를 할당할 때, 변수의 크기는 성능의 차이를 주지않는다.
  >
  >- **Why?** 크기가 10000짜리 변수를 항상하든 크기가 4짜리 변수를 할당하든, 둘다 [ebp-4], [ebp-10000]이므로 연산상의 성능차이가 없다.
  >  - **BUT** debug build에선 다르다. 스택 프레임을 0xCCCCCCCC로 미는 과정이 발생하여, 변수가 커질수록 스택프레임의 크기가 커지므로 해당 과정에서 비용이 발생한다.
  >  - 따라서 실제 제품 출시 시에 어쩔 수없이 bebug build로 출시해야하는 경우가 생길 수 있는데, 이때는 최대한 지역변수의 크기를 줄이는 것이 성능향상에 도움이 된다.

<br>

### Assembly 코드 분석

```assembly
push        ebp
mov         ebp, esp

*push 연산은 32bit 머신에서는 4씩 64bit머신에서는 8씩 내림.
```

- ebp를 스택에 저장하고, esp값을 ebp로 옮긴다.

- 여기부터 새로운 스택 프레임의 시작점 이므로, ebp의 내용을 백업하고 esp를 ebp에 덮어 씌운다.

<br>

```assembly
sub         esp, 0E4h

*0E4h앞에 0이 붙은 것은 아무 의미없음. Visual Studio에서 숫자 맨처음이 알파벳으로 시작하면
 0을 앞에 붙히는 현상이 발생
```

- esp를 0E4h만큼 빼면서, 스택의 사이즈를 0E4h로 잡는다. 즉 228 byte의 메모리를 잡은 것이다.

- ebp는 스택 프레임의 시작지점. esp는 스택 프레임의 끝 지점을 나타낸다. 따라서, 스택 프레임의 범위는 ebp - esp가 된다.

- debug build라 0E4h로 스택 크기를 잡은 것이고, release build에서는 딱 사용하는 지역 변수의 크기만큼만 잡는다.

> ***PLUS.*** 이 단계에서 이미 스택에서 사용되는 지역 변수의 메모리의 확보가 다 끝난다.
>
> ```c
> void func()
> {
> 	int a;
> 
> 	if (a == 0)
> 	{
> 		int x = 1;
> 	}
> }
> ```
>
>  그러면 위와 같이 `{}`로 스코프가 나뉘는 경우에서는 중괄호 안에 있는 변수 x는 어느 시점에 메모리가 잡힐까?
>
> -> 당연히 함수가 맨처음 시작될 때 잡힌다. 컴파일러가 함수를 전부 탐색하며 지역 변수 선언된 것들의 모든 합산 크기를 구할 것이고, 그 크기에 맞춰서 스택 크기를 잡는다.



```assembly
push        ebx
push        esi
push        edi
```

- ebs, esi, edi 레지스터를 백업한다. 이는 debug build 에서만 작용하며, 의미 없는 과정이다. 범용 레지스터들을 백업하는 순간부터 정상적인 프로세스는 아니다.



```assembly
lea         edi, [ebp-0E4h]
mov         ecx, 39h
mov         eax, 0CCCCCCCCh
rep stos    dword ptr es: [edi]

*lea는 기능상 mov와 같음. 하지만 주소를 계산한다는 것을 구분하기 위해, 만들어짐.
*보통 대괄호([])는 C에서 *의 의미를 가지지만, lea에서는 의미없음. 그냥 주소가 들어감.

*rep은 반복문을 나타내는 명령어로, 스택의 맨위부터 시작하여 0xCCCCCCCC로 밀어버리는 과정을 
 반복함 
```

- 이 부분도 debug build에서만 나오는 부분이다. release build에서는 위의 두과정이 존재하지 않는다.

- 스택프레임의 값을 0xCCCCCCCC로 밀어버리는 과정이다.

  > ***PLUS.*** 사실상 변수가 초기화되기 이전에 0xCCCCCCCC는 쓰레기값이 아닌 컴파일러에서 디버깅을 돕기위해 초기화해둔 값이다. 이는 메모리의 사용여부, 해체여부를 편하게 확인할 수 있다

- ecx에 반복할 횟수를 넣는 데, 228 / 4인 57을 넣고 모든 메모리를 이 값으로 밀어버린다.

  > ***PLUS.*** Visual Studio 2022기준 전체 스택을 cc로 밀지않고 사용하는 공간만 cc로 민다.



```assembly
mov         dword ptr [ebp-8], 1    --> [a]
mov         dword ptr [ebp-14h], 2  --> [b]

*실제변수 앞과 뒤에 padding을 두었음. 본래는 4바이트만 사용하는 것이 맞음.
*모든 변수는 ebp를 기준으로 얼마만큼 떨어진 곳에 있는지로 인식됨.
```

- 변수에 값을 대입하는 부분. a는 [ebp - 8]로 대체되었으며, 이는 a가 ebp로부터 8byte 떨어진 부분을 사용하고 있다는 뜻이다.



```assembly
mov         eax, dword ptr [ebp-8]
add         eax, dword ptr [ebp-14h]
mov         dword ptr [ebp-20h], eax

*모든 연산은 레지스터에서 이루어짐.
```

- `c = a + b` 부분. 모든 연산은 레지스터에서 이루어지며, 따라서 메모리에서 레지스터로 옮겨오는 과정이 필수적으로 나타남.



```assembly
imul        eax, dword ptr [ebp-8], 3
mov         dword ptr [ebp-20h], eax
```

- `c = a * 3` 부분. [a]를 eax로 불러와서 3을 곱한뒤에 그 값을 [c]로 옮김.
> ***PLUS.*** 메모리 상에서 숫자가 반대로 써있는 이유.
> 0x001bfb84를 메모리 상에서 보면 84 fb 1b 00 으로 반대로 써있다.  
> 이는 CPU가 메모리를 읽는 방법이 “리틀 엔디안” 방식이기 때문이다.  
> 그의 반대는 빅 엔디안.  
>
> 우리가 프로그래밍하는 프로세서는 리틀 엔디안 시스템이다. 그런데 네트워크 장비들은 빅 엔디안 시스템이 표준이다. 따라서 네트워크 장비에서는 빅 엔디안 시스템을 접해볼 수 있음.
>
> ![image-20230830192027899](https://i.imgur.com/QDMilM9.png)



```assembly
pop         edi  
pop         esi  
pop         ebx
  
add         esp,0E4h  
cmp         ebp,esp  
call        __RTC_CheckEsp (04B1235h)  
mov         esp,ebp  
pop         ebp  
ret
```

- 함수의 코드가 모두 끝나면 위와 같은 어셈블리 코드로 함수를 정리한다.

   

```assembly
pop         edi  
pop         esi  
pop         ebx
```

- 앞서 백업해놨던 edi, esi, ebx의 레지스터 값들을 복원한다.

```assembly
add         esp,0E4h 
```

- esp에 0E4h를 더해줌으로 써, 확보했던 스택 공간을 다시 반납한다.

```assembly
cmp         ebp,esp  
call        __RTC_CheckEsp (04B1235h)  
mov         esp,ebp 

*cmp는 두 값을 빼서 결과가 0이면 같다고 판단한다.
 cmp에서 빼진 결과는 ZeroFlag 레지스터에 들어가고 jmp관련 명령어는 모두 해당 레지스터를 참조.
```

- 스택이 깨졋는지를 검증하기 위해 ebp와 esp의 값을 비교한다.
- 다르다면 `__RTC_checkEsp`에서 에러 메시지를 띄울 것이다. (debug build에서만 해당)
- 원래대로라면 `mov esp, ebp`만 하는 것이 이상적인 코드이고, debug build이기 때문에 한번 검증하는 코드가 들어간 것이다.



```assembly
pop         edi  
pop         esi  
pop         ebx
```

- 백업 했던 ebp의 값을 다시 가져오고 함수를 끝낸다.



### 최적화 컴파일

- 컴파일러가 소스코드를 다 뒤집어 엎어, 의미가 없는 코드를 다 제거해버림.
- 빌드시간과 성능이 향상된다는 장점이 있지만, 어셈블리로 나온 코드가 내가 짠 코드와 완전 달라지게 되므로, 디버깅시 굉장히 큰 어려움이 있음.

따라서 우리는 개발시에 기본 개발환경을 **Release Build + 최적화 컴파일 비활성화**로 간다. 이러면 내가 짠 코드대로만 어셈블리가 생성될 것이고, 디버그 빌드에서 사용되었던 안전장치들이 빠진 상태가 된다.

이 기본 개발환경에서 개발을 하고 debug build에서 추가로 테스트를 병행하는 것으로 간다.