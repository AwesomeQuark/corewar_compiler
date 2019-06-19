#include <libc.h>


int		one_try(void)
{
	int good_room = random() / (2147483647 / 3);
	int choice = random() / (2147483647 / 3);
	int	new_choice = choice;
	int	eliminated = good_room;

	while (eliminated == good_room || eliminated == choice)
		eliminated = random() / (2147483647 / 3);
	while (new_choice == choice || new_choice == eliminated)
		new_choice = random() / (2147483647 / 3);
	if (new_choice == good_room)
		return (1);
	else
		return (0);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		return (printf("Enter a number\n"));

	int		attempts = atoi(argv[1]);
	int		i = attempts;
	int		tot = 0;

	srandom(time(NULL));
	while (i-- >= 0)
		tot += one_try();

	printf("Result : %d winrate / %d attempts", (tot * 100) / attempts, attempts);

	return (0);
}