#include <iostream>
using namespace std;
const int N = 3, M = 4;
void print(int n, int m, int A[], int B[], int x[][M + 1], int c[][M + 1], int difa[] = NULL, int difb[] = NULL)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cout << "\t";
			if (x[i][j] == -2)
				cout << 0;
			else if (x[i][j] > 0)
				cout << x[i][j];
			cout << "(" << c[i][j] << ")";
		}
		cout << "\t" << A[i];

		if (difa != NULL)
		{
			cout << "\t| ";
			if (difa[i] != -1)
				cout << difa[i];
			else
				cout << "-";
		}
		cout << endl;
	}
	for (i = 0; i < m; i++)
		cout << "\t" << B[i];
	cout << endl;

	if (difb != NULL)
	{
		cout << "\t_\t_\t_\t_\t_\n";
		for (i = 0; i < m; i++)
		{
			cout << "\t";
			if (difb[i] != -1)
				cout << difb[i];
			else
				cout << "-";
		}
		cout << endl;
	}
}

void sort(int n, int A[])
{
	int i, j, k, obm;
	for (i = 0; i < n - 1; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (A[k] > A[j])
				k = j;
		}
		if (k != i)
		{
			obm = A[k];
			A[k] = A[i];
			A[i] = obm;
		}
	}
}

int minind(int i, int ind, int n, int c[][M + 1], int x[][M + 1], bool ver = false)
{
	int j, k, * A = new int[n];
	for (j = 0, k = 0; j < n; j++)
	{
		if (!ver)
		{
			if (x[i][j] == -1)
			{
				A[j] = c[i][j];
				k++;
			}
			else
				A[j] = -1;
		}
		else
		{
			if (x[j][i] == -1)
			{
				A[j] = c[j][i];
				k++;
			}
			else
				A[j] = -1;
		}
	}
	if (k == 0)
	{
		delete[] A;
		return -1;
	}

	sort(n, A);
	/*for (j = 0; j < n; j++)
		cout << " " << A[j];
	cout << endl;*/
	if (k - 1 < ind)
	{
		delete[] A;
		return 0;
	}
	j = A[n - k + ind];
	delete [] A;
	return j;
}

int find(int i, int a, int n, int c[][M + 1], int x[][M + 1], bool ver = false)
{
	int j;
	for (j = 0; j < n; j++)
	{
		if ((!ver && (a == c[i][j]) && (x[i][j] == -1)) || (ver && (a == c[j][i]) && (x[j][i] == -1)))
			return j;
	}
	return -1;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int i, j, imin, jmin, min, max, iv, jv, n = N, m = M, s1 = 0, s2 = 0, difa[N + 1], difb[M + 1], x[N + 1][M + 1], c[N + 1][M + 1] =
	{
		/*13, 14, 12, 9, 11, 0,
		16, 17, 14, 12, 15, 0,
		18, 16, 15, 15, 16, 0,
		0, 0, 0, 0, 0, 0,*/

		/*12, 13, 11, 8, 10, 0,
		9, 10, 7, 5, 8, 0,
		10, 8, 7, 7, 8, 0,
		0, 0, 0, 0, 0, 0,*/

		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,

		/*1, 1, 1, 1, 0,
		1, 1, 1, 1, 0,
		1, 1, 1, 1, 0,
		0, 0, 0, 0, 0,*/
	};
	//int A[N + 1] = { 51, 46, 99 }, B[M + 1] = { 74, 23, 90, 49, 34 };
	//int A[N + 1] = { 88, 6, 92 }, B[M + 1] = { 32, 62, 54, 10, 78 };
	int A[N + 1] = { 0, 0, 0 }, B[M + 1] = { 0, 0, 0, 0 };
	//int A[N + 1] = { 2, 2, 2 }, B[M + 1] = { 1, 1, 1, 1 };
	bool f, ver;
	for (i = 0; i <= N; i++)
	{
		for (j = 0; j <= M; j++)
			x[i][j] = -1;
	}
	print(n, m, A, B, x, c);

	for (i = 0; i < N; i++)
		s1 += A[i];
	for (i = 0; i < M; i++)
		s2 += B[i];
	if (s1 != s2)
	{
		cout << " Модель открытая (суммарные запасы = " << s1 << ", суммарные потребности = " << s2 << ").\n\n";
		if (s1 > s2)
		{
			m++;
			B[M] = s1 - s2;
		}
		else if (s1 < s2)
		{
			n++;
			A[N] = s2 - s1;
		}
		print(n, m, A, B, x, c);
	}
	cout << " Модель закрытая.\n\n";

	//int k = 0;
	while (1)
	{
		//k++;
		cout << "______________________\n";
		s1 = 0;
		s2 = 0;
		for (i = 0; i < n; i++)
			s1 += A[i];
		for (i = 0; i < m; i++)
			s2 += B[i];
		if ((s1 == 0) && (s2 == 0))
			break;

		for (i = 0; i < n; i++)
		{
			if ((minind(i, 1, m, c, x) == -1) && (minind(i, 0, m, c, x) == -1))
				difa[i] = -1;
			else
				difa[i] = abs(minind(i, 1, m, c, x) - minind(i, 0, m, c, x));
		}
		for (i = 0; i < m; i++)
		{
			if ((minind(i, 1, n, c, x, true) == -1) && (minind(i, 0, n, c, x, true) == -1))
				difb[i] = -1;
			else
				difb[i] = abs(minind(i, 1, n, c, x, true) - minind(i, 0, n, c, x, true));
		}

		//print(n, m, A, B, x, c, difa, difb);



		ver = false;
		max = -1;
		for (i = 0; i < n; i++)
		{
			if ((max < difa[i]) || ((max == difa[i]) && (min > minind(i, 0, m, c, x))))
			{
				max = difa[i];
				imin = i;
				min = minind(i, 0, m, c, x);
			}
		}
		//cout << "max = " << max << " imin = " << imin << " min = " << min << endl;

		for (i = 0; i < m; i++)
		{
			if ((max < difb[i]) || ((max == difb[i]) && (min > minind(i, 0, n, c, x, true))))
			{
				max = difb[i];
				imin = i;
				min = minind(i, 0, n, c, x, true);
				ver = true;
			}
		}
		//cout << "max = " << max << " imin = " << imin << " min = " << min << endl;

		if (!ver)
			jmin = find(imin, min, m, c, x, ver);
		else
		{
			jmin = find(imin, min, n, c, x, ver);
			i = jmin;
			jmin = imin;
			imin = i;
		}
		cout << " i = " << imin << ", j = " << jmin << endl;


		f = false;
		if (A[imin] >= B[jmin])
		{
			x[imin][jmin] = B[jmin];
			A[imin] -= B[jmin];
			B[jmin] = 0;
			for (i = 0; i < n; i++)
			{
				if (x[i][jmin] == -1)
				{
					x[i][jmin] = 0;
					if (!f && A[imin] == 0)
					{
						x[i][jmin] = -2;
						f = true;
					}
				}
			}
		}
		else
		{
			x[imin][jmin] = A[imin];
			B[jmin] -= A[imin];
			A[imin] = 0;
			for (i = 0; i < m; i++)
			{
				if (x[imin][i] == -1)
					x[imin][i] = 0;
			}
		}
		print(n, m, A, B, x, c, difa, difb);
	}



	s1 = 0;
	s2 = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			f = false;
			if (x[i][j] == -2)
			{
				x[i][j] = 0;
				f = true;
			}
			s1 += x[i][j] * c[i][j];
			if (f)
				x[i][j] = -2;
			if ((x[i][j] != 0) && (x[i][j] != -1))
				s2++;
		}
	}
	s2 = n + m - 1 - s2;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cout << "\t";
			if (x[i][j] == -2)
				cout << 0;
			else if ((x[i][j] <= 0) && (s2 > 0))
			{
				cout << 0;
				s2--;
			}
			else if (x[i][j] > 0)
				cout << x[i][j];
			cout << "(" << c[i][j] << ")";
		}
		cout << "\t" << A[i] << endl;
	}
	for (i = 0; i < m; i++)
		cout << "\t" << B[i];
	cout << endl;

	cout << " z = " << s1;
	return 0;
}