#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

std::vector<double> normalize(const std::vector<double>& mtr)
{
    std::vector<double> _mtr(4);
    double s = 0;
    for (auto i : mtr)
        s += i;
    for (int i = 0; i < 4; i++)
        _mtr[i] = mtr[i] / s;
    return _mtr;
}

std::vector<std::vector<double>> normalize(const std::vector<std::vector<double>>& mtr)
{
    std::vector<double> sum(4);
    std::vector<std::vector<double>> _mtr(4, std::vector<double>(4));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sum[i] += mtr[j][i];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            _mtr[j][i] = mtr[j][i] / sum[i];
    return _mtr;
}

void sort(std::vector<std::vector<double>>& mtr)
{
    double tmp;
    for (auto i = 0; i < 4; i++)
        for (auto j = 0; j <= 3; j++)    
            for (auto c = j; c <= 3; c++)   
                if (mtr[j][i] > mtr[c][i])
                {
                    tmp = mtr[j][i];
                    mtr[j][i] = mtr[c][i];
                    mtr[c][i] = tmp;
                }
}

std::vector<std::vector<double>> metod_zameny(const std::vector<std::vector<double>>& mtr, const int& crit)
{
    std::vector<std::vector<double>> mtr1 = mtr;
    sort(mtr1);
    std::vector<std::vector<double>> mtr2(4, std::vector<double>(4));

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i != crit)
                mtr2[j][i] = (mtr[j][i] - mtr1[0][i]) / (mtr1[3][i] - mtr1[0][i]);
            else
                mtr2[j][i] = mtr[j][i];
        }
    return mtr2;
}

double metod_Pareto_utopia(const std::vector<std::vector<double>>& mtr, const int& crit)
{
    std::vector<double> _mtr(4);
    for (int i = 0; i < 4; i++)
        _mtr[i] = mtr[i][crit];
    sort(begin(_mtr), end(_mtr));
    return _mtr[3];
}

double metod_Pareto_Euclid(const std::vector<std::vector<double>>& mtr, const double& ut1, const double& ut2, const int& crit1, const int& crit2, const int& crit3)
{
    double dist;
    dist = sqrt(pow(ut1 - mtr[crit3][crit1], 2) + pow(ut2 - mtr[crit3][crit2], 2));
    return dist;
}

std::vector<double> vector_of_weights(const std::vector<double>& crit)
{
    std::vector<double> vec_crit(4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i != j)
            {
                if (crit[i] > crit[j])
                    vec_crit[i]++;
                if (crit[i] == crit[j])
                    vec_crit[i] += 0.5;
            }
    return vec_crit;
}

std::vector<double> metod_vzveshivaniya(const std::vector<std::vector<double>>& mtr, const std::vector<double>crit)
{
    std::vector<double> _mtr(4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            _mtr[i] += mtr[i][j] * crit[j];
    return _mtr;
} 

std::vector<std::vector<double>> metod_ierarchy_matrix(const std::vector<std::vector<double>>& mtr, const int& crit)
{
    std::vector<std::vector<double>> _mtr(4, std::vector<double>(4));
    for (int i=0;i<4;i++)
        for (int j = 0; j < 4; j++)
        {
            if (mtr[i][crit] == mtr[j][crit])
                _mtr[i][j] = 1;
            if (mtr[i][crit] > mtr[j][crit])
            {
                if (mtr[i][crit] - mtr[j][crit] == 1) 
                    _mtr[i][j] = 3;
                if (mtr[i][crit] - mtr[j][crit] == 2)
                    _mtr[i][j] = 5;
                if (mtr[i][crit] - mtr[j][crit] == 3)
                    _mtr[i][j] = 7;
                if (mtr[i][crit] - mtr[j][crit] == 4)
                    _mtr[i][j] = 9;
            }
            if (mtr[i][crit] < mtr[j][crit])
            {
                if (mtr[j][crit] - mtr[i][crit] == 1) 
                    _mtr[i][j] = 1.0 / 3;
                if (mtr[j][crit] - mtr[i][crit] == 2)
                    _mtr[i][j] = 1.0 / 5;
                if (mtr[j][crit] - mtr[i][crit] == 3)
                    _mtr[i][j] = 1.0 / 7;
                if (mtr[j][crit] - mtr[i][crit] == 4) 
                    _mtr[i][j] = 1.0 / 9;
            }
        }
    return _mtr;
}

std::vector<std::vector<double>> metod_ierarchy_criterions(const std::vector<double>& crit)
{
    std::vector<std::vector<double>> _mtr(4, std::vector<double>(4));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (crit[i] == crit[j]) 
                _mtr[j][i] = 1;
            if (crit[i] > crit[j])
            {
                if (crit[i] - crit[j] == 1) 
                    _mtr[j][i] = 3;
                if (crit[i] - crit[j] == 2) 
                    _mtr[j][i] = 5;
                if (crit[i] - crit[j] == 3)
                    _mtr[j][i] = 7;
                if (crit[i] - crit[j] == 4) 
                    _mtr[j][i] = 9;
            }
            if (crit[i] < crit[j])
            {
                if (crit[j] - crit[i] == 1)
                    _mtr[j][i] = 1.0 / 3;
                if (crit[j] - crit[i] == 2) 
                    _mtr[j][i] = 1.0 / 5;
                if (crit[j] - crit[i] == 3)
                    _mtr[j][i] = 1.0 / 7;
                if (crit[j] - crit[i] == 4)
                    _mtr[j][i] = 1.0 / 8;
            }
        }
    return _mtr;
}

std::vector<double> summa(const std::vector<std::vector<double>>& mtr)
{
    std::vector<double> sum(4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            sum[i] += mtr[i][j];
    return sum;
}

void print(const std::vector<double>& mtr)
{
    for (auto i : mtr) std::cout << i << " ";
    std::cout << std::endl;
}

void print(const std::vector<std::vector<double>>& mtr)
{
    std::cout << "     1     2     3    4" << std::endl;
    std::cout << "A  ";
    for (int i = 0; i < 4; i++) std::cout << std::fixed << std::setprecision(2) << mtr[0][i] << "  ";
    std::cout << std::endl << "B  ";
    for (int i = 0; i < 4; i++) std::cout << mtr[1][i] << "  ";
    std::cout << std::endl << "C  ";
    for (int i = 0; i < 4; i++) std::cout << mtr[2][i] << "  ";
    std::cout << std::endl << "D  ";
    for (int i = 0; i < 4; i++) std::cout << mtr[3][i] << "  ";
    std::cout << std::endl;
}

void print(const std::vector<std::vector<double>>& mtr, const std::vector<double>& sum, const std::vector<double>& normsum)
{
    std::cout << "     A      B      C      D     sum   NormSum" << std::endl;
    std::cout << "A  ";
    for (int i = 0; i <= 3; i++) 
        std::cout << std::fixed << std::setprecision(2) << std::setw(5) << mtr[0][i] << "  ";
    std::cout << std::setw(5) << sum[0] << "  " << normsum[0];
    std::cout << std::endl << "B  ";
    for (auto i = 0; i <= 3; i++) 
        std::cout << std::setw(5) << mtr[1][i] << "  ";
    std::cout << std::setw(5) << sum[1] << "  " << normsum[1];
    std::cout << std::endl << "C  ";
    for (auto i = 0; i <= 3; i++)
        std::cout << std::setw(5) << mtr[2][i] << "  ";
    std::cout << std::setw(5) << sum[2] << "  " << normsum[2];
    std::cout << std::endl << "D  ";
    for (auto i = 0; i <= 3; i++) 
        std::cout << std::setw(5) << mtr[3][i] << "  ";
    std::cout << std::setw(5) << sum[3] << "  " << normsum[3];
    std::cout << std::endl;
}


int main()
{
    std::vector<std::vector<double>> mtr = { {7,7,3,6},{9,4,2,8},{3,6,8,7},{6, 8,6,4} };
    std::vector<double> crit = { 6,4,2,8 };
    std::vector<double> norm_crit = normalize(crit);
    print(mtr);
    print(norm_crit);

    std::cout << std::endl << "Metod zameny kriteriev ogranicheniyami: " << std::endl;
    //criterion: 3
    std::vector<std::vector<double>> mtr1 = metod_zameny(mtr, 3);
    print(mtr1);

    std::cout << std::endl << "Metod Pareto (Euclid distance): " << std::endl;
    //criterions: 1, 2
    double ut1 = metod_Pareto_utopia(mtr, 1);
    double ut2 = metod_Pareto_utopia(mtr, 2);
    std::cout << "Utopias " << ut1 << " " << ut2 << std::endl;
    std::cout << "A: " << metod_Pareto_Euclid(mtr, ut1, ut2, 1, 2, 0) << std::endl;
    std::cout << "B: " << metod_Pareto_Euclid(mtr, ut1, ut2, 1, 2, 1) << std::endl;
    std::cout << "C: " << metod_Pareto_Euclid(mtr, ut1, ut2, 1, 2, 2) << std::endl;
    std::cout << "D: " << metod_Pareto_Euclid(mtr, ut1, ut2, 1, 2, 3) << std::endl;

    std::cout << std::endl << "Metod vzveshivaniya: " << std::endl;
    std::vector<std::vector<double>> mtr2 = normalize(mtr);
    print(mtr2);
    std::vector<double> vec_crit;
    std::vector<double> norm_vec_crit;
    vec_crit = vector_of_weights(crit);
    norm_vec_crit = normalize(vec_crit);
    print(norm_vec_crit);
    vec_crit = metod_vzveshivaniya(mtr2, norm_vec_crit);
    std::cout << "Znacheniya kriteria: ";
    print(vec_crit);
    std::cout << std::endl << std::endl;


    std::cout << "Metod ierarchy: " << std::endl;
    std::vector<double> _mtr0(4), _mtr1(4), _mtr2(4), _mtr3(4), _mtr(4);
    std::vector <double> mtr0sum(4), mtr1sum(4), mtr2sum(4), mtr3sum(4), mtrsum(4);

    mtr2 = metod_ierarchy_matrix(mtr, 0);
    mtr0sum = summa(mtr2);
    _mtr0 = normalize(mtr0sum);
    std::cout << std::endl << "Appearence: " << std::endl;
    print(mtr2, mtr0sum, _mtr0);

    mtr2 = metod_ierarchy_matrix(mtr, 1);
    mtr1sum = summa(mtr2);
    _mtr1 = normalize(mtr1sum);
    std::cout << std::endl << "Financial requets: " << std::endl;
    print(mtr2, mtr1sum, _mtr1);

    mtr2 = metod_ierarchy_matrix(mtr, 2);
    mtr2sum = summa(mtr2);
    _mtr2 = normalize(mtr2sum);
    std::cout << std::endl << "Thriftiness: " << std::endl;
    print(mtr2, mtr2sum, _mtr2);

    mtr2 = metod_ierarchy_matrix(mtr, 3);
    mtr3sum = summa(mtr2);
    _mtr3 = normalize(mtr3sum);
    std::cout << std::endl << "Personality: " << std::endl;
    print(mtr2, mtr3sum, _mtr3);

    mtr2 = metod_ierarchy_criterions(crit);
    mtrsum = summa(mtr2);
    _mtr = normalize(mtrsum);
    std::cout << std::endl << "Priority of criterions: " << std::endl;
    print(mtr2, mtrsum, _mtr);
    std::cout << std::endl;

    for (int i = 0; i < 4; i++)
    {
        mtr2[i][0] = _mtr0[i];
        mtr2[i][1] = _mtr1[i];
        mtr2[i][2] = _mtr2[i];
        mtr2[i][3] = _mtr3[i];
    }
    for (auto i : mtr2)
    {
        for (auto j : i) 
            std::cout << j << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    vec_crit = metod_vzveshivaniya(mtr2, _mtr);
    print(vec_crit);
}

