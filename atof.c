#include <stdio.h>
#include <math.h>

/*
double	atof(char *nbr)
{

}
*/

int	count_digits_int(int nr)
{
	int	digits_count;

	digits_count = 1 + (nr < 0);
	while (nr / 10 != 0)
	{
		digits_count++;
		nr = nr / 10;
	}
	return (digits_count);
}

int	count_digits_fraction(double nr, int precision)
{
	int	digits_count;

	digits_count = 2 + (nr < 0);
	if (nr < 0)
		nr *= -1;
	while (nr / 0.1 > 0 || !precision)
	{
		printf("%f / 0.1 = %f\n", nr, nr / 0.1);
		digits_count++;
		precision--;
		nr = remainder(nr, 0.1) * 10;
	}
	return (digits_count);
}
/*
int	count_digits_double(double nr)
{
	int	digits;

	digits = 0 + (nr < 0);
	while (nr / 10 > 0)
}
*/
int	main(void)
{
	double db = 0.123456;

/*	db = -0.0123;
	printf("%f / 0.1 = %f\n", db, db / 0.1);
	db = remainder(db, 0.1) * 10;
	if (db == 0)
		printf("ZERO %f\n", db);
	printf("%f / 0.1 = %f\n", db, db / 0.1);
	db = remainder(db, 0.1) * 10;
	printf("%f / 0.1 = %f\n", db, db / 0.1);
	db = remainder(db, 0.1) * 10;
	printf("%f / 0.1 = %f\n", db, db / 0.1);
	db = remainder(db, 0.1) * 10;
	printf("%f / 0.1 = %f\n", db, db / 0.1);
	db = remainder(db, 0.1);
	if (db == 0)
		printf("ZERO %f\n", db);
*/
/*	printf("%f %% 0.1 = %f\n", db, remainder(db, 0.1));
	return (0);
*/
/*	printf("sizeof(double) = %zu\n", sizeof(double));
	printf("%f is %.34f\n", db, db); return (0);
*/
	printf("%f has %d digits\n", db, count_digits_fraction(db, 10));
	return (0);

	int	n = 0;

	printf("%d has %d digits\n", n, count_digits_int(n));
	return (0);

	double	d = 1283.72;
	int		i = (int)d;

	printf("%d\n", i);
	printf("%f\n", d - i);
	return (0);
}
