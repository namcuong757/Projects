#include "option.h"

int main(int num, char** agrv)
{
	option options;
	options = get_option(num, agrv);
	return 0;
}
