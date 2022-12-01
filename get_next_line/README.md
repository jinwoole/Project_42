# get_next_line 끝내고 대충 기록

### get_next_line, 뭐하는 함수인가?
이 함수는 파일 디스크립터를 받아서, 그것의 next line을 get하는 함수.
#### 매개변수
> 파일 디스크립터
#### 리턴값
> 별 문제 없으면, get_next_line은 \n으로 끊긴 문자열을 return한다.
> 에러시 NULL return
---
### gnl과 친구들
#### 1. read_to_backup
> file descriptor을 받아서 buff에 저장한 후, 정적변수 backup_str에 합쳐서 저장한다.
#### 2. get_line
> bakcup_str에서 line을 뽑아내서 return한다. if(\n), \0가 있는 완전한 문자열.
#### 3. new_backup_str
> get_line에서 return한 값을 제외한 값으로 정적변수를 업데이트해서 새로 읽을 준비를 한다.
--
__-
#### read로 다 해먹기에는 read는 시스템콜이라 비용이 많이 든다.
