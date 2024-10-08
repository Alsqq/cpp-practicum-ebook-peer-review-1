#include <iostream>
#include <vector>

using namespace std;

class Ebook
{
public:
    Ebook() : users_count_(1000, 0), pages_to_user_(1e+5 + 1, 0) {}

    void Read(size_t user, size_t pages)
    {
        size_t pages_before = 0;

        if (pages_to_user_[user])
        {
            pages_before = pages_to_user_[user];
        }
        else
        {
            ++people_;
        }

        pages_to_user_[user] = pages;

        for (size_t i = pages_before; i < pages; ++i)
        {
            users_count_[i] += 1;
        }
    }

    double Cheer(size_t user)
    {
        if (!pages_to_user_[user])
        {
            return 0.0;
        }
        else if (!(people_ - 1))
        {
            return 1.0;
        }
        else
        {
            size_t pages_to_user = pages_to_user_[user];
            if (people_ == users_count_[pages_to_user - 1])
            {
                return 0.0;
            }
            else
            {
                return (people_ - users_count_[pages_to_user - 1]) /
                       (people_ * 1.0 - 1.0);
            }
        }
    }

private:
    vector<size_t> users_count_; // лучше переименовать переменную, чтобы было
                                 // понятнее, для чего именно ведется отсчет
    vector<size_t>
        pages_to_user_; // также лучше переименовать, поскольку по названию
                        // ожидается обращение по номеру страницы и получение
                        // пользователя, а не наоборот

    size_t people_ = 0; // также лучше переименовать переменную, чтобы было
                        // понятнее, что она хранит количество пользователей, а
                        // не просто людей
};

void ExecuteQueries(istream &input, ostream &output, Ebook &ebook)
{
    string str;
    getline(input, str);

    size_t requests_amount = stoi(str);

    for (size_t i = 0; i < requests_amount; ++i)
    {
        string request_type;
        getline(input, request_type, ' ');
        if (request_type == "READ")
        {
            string user;
            getline(input, user, ' ');

            string pages;
            getline(input, pages);

            ebook.Read(stoi(user), stoi(pages));
        }
        else
        {
            string user;
            getline(input, user);
            output << ebook.Cheer(stoi(user)) << endl;
        }
    }
}

int main()
{
    Ebook ebook;
    ExecuteQueries(cin, cout, ebook);
}