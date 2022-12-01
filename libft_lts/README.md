# libft_lts
My 42library

### 사용
1. 클론
2. setting_libft 실행
3. 프로젝트 헤더에 libft헤더 포함
```c
#include "./includes/libft.h"
```
It'll include all libft functions including GNL and ft_printf  
or not  
+norm checked

### lst함수에 대한 간략한 메모

t_list 첫번째 node는 head node개념으로 사용. 값 입력, 사용x

그러니까 lst_add_front는 가능한 사용하지 않으면 좋다.  
lstprint 등 함수들도 이 기준에 맞춰져 있음
lstselect함수의 index의 1도 두번째 노드. 0도 있어야 하긴 하지.

### ft_printtf에 대한 간략한 메모
가변인자들 뭐 대충 받아넣으면 잘 나옴.
\n까진 되게 했고, 나머지 옵션들은 안넣음.
애플실리콘 맥 환경에선(2022.3.21기준) va_arg가 의도대로 작동하지 않아 가변인수 1개 초과해서 넣으면 다음껄 못읽음.
다양한 환경에 대응할 방법이... 있나?
