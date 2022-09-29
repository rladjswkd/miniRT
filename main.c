#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
/*
ARGUMENTS PARSING
1. 파일의 확장자는 ".rt"여야 한다.
2. 한 라인 안에 여러 개의 공백이 연달아 있을 때 다음 필드 값이 나올 때까지 정상적으로 공백들을 넘길 수 있어야 한다. (어떠한 동적 할당도 없이) 
3. 한 줄을 읽었을 때 단순히 개행 문자로만 구성된 문자열이면 아무런 동적할당 없이 넘길 수 있어야 한다.
4. 파일 내에서 각 구성 요소가 주어지는 순서는 정해지지 않는다.
5. "알파벳 대문자로 정의된" 구성 요소들은 한 번만 주어진다. 따라서 동일한 알파벳 대문자가 여러 번 나온다면 입력 오류다.
6. pdf를 보고, 입력 파일에서 각 구성 요소들의 정보가 주어지는 형태를 확인하고, 오류 처리를 해주자.
7. 위의 경우에서 벗어나는 입력 파일이 들어온 경우, "Error\n"을 출력하고,  상황에 맞는 명시적인 정보를 출력한 후 정상적으로 종료해야 한다.
*/

int	main(int argc, char **argv)
{
	int		fd;
	char	*p;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (0); // 에러 문자열 출력하고 처리해주기
		while (1) // 개행문자만 나오면 넘기기
		{
			p = get_next_line(fd);
			if (p[0] == '\n')
				continue ;
		}
	}
	return (0);
}