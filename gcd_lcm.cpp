#include <iostream> // for input/output
#include <string>   // for std::string
#include <map>      // for std::map (stores prime factors and their powers)
#include <cmath>    // for pow() function

using namespace std;

int main()
{
    while (true) // infinite loop, keeps asking user until program is stopped
    {
        // Global maps to hold prime factors and their counts
        map<int, int> number1; // prime factors of first number
        map<int, int> number2; // prime factors of second number
        map<int, int> sum;     // used to build result (for GCD/LCM)
        int num1 = 0, num2 = 0, result = 1;
        string gcdlcm = "";

        // Take two numbers from the user
        cout << "Please enter 2 numbers.\nNumber 1: ";
        cin >> num1;
        cout << "Number 2: ";
        cin >> num2;

        // PRIME FACTORIZATION OF num1
        for (int i = 2; i <= num1;)
        {
            if (num1 % i == 0) // if i divides num1
            {
                if (!number1[i]) // if i is not already in map
                {
                    number1[i] = i;  // initially store the prime itself
                    number1[i] += 1; // then increment → first exponent = 1
                    num1 /= i;       // divide num1 by i
                }
                else
                {
                    number1[i] += 1; // if already exists, increment exponent
                    num1 /= i;       // divide num1 by i
                }
            }
            else
            {
                i++; // try next divisor
            }
        }

        // PRIME FACTORIZATION OF num2 (same logic)
        for (int i = 2; i <= num2;)
        {
            if (num2 % i == 0)
            {
                if (!number2[i])
                {
                    number2[i] = i;
                    number2[i] += 1;
                    num2 /= i;
                }
                else
                {
                    number2[i] += 1;
                    num2 /= i;
                }
            }
            else
            {
                i++;
            }
        }

        // Adjust the values: subtract prime itself from exponent storage
        // (because earlier logic stored prime + exponent instead of just exponent)
        for (auto &numara : number1)
        {
            numara.second = numara.second - numara.first;
        }
        for (auto &numara : number2)
        {
            numara.second = numara.second - numara.first;
        }

    start:
        // Ask user if they want GCD or LCM
        cout << "Do you want to get the GCD or the LCM of those 2 numbers: ";
        cin >> gcdlcm;

        if (gcdlcm == "GCD")
        {
            if (num1 == 0 || num2 == 0) // if one is zero
            {
                cout << "0" << endl;
            }
            else
            {
                // Compare prime powers in both maps
                for (auto &[key, val1] : number1)
                {
                    auto it = number2.find(key); // check if prime also in number2
                    if (it != number2.end())
                    {
                        int val2 = it->second;
                        // For GCD, take the smaller exponent of each prime
                        if (val1 == val2)
                        {
                            sum[key] = val1;
                        }
                        else if (val1 < val2)
                        {
                            sum[key] = val1;
                        }
                        else if (val2 < val1)
                        {
                            sum[key] = val2;
                        }
                    }
                }

                // Multiply primes^exponent together
                for (const auto &[key, val] : sum)
                {
                    cout << "Number " << key << " exist " << val << " times." << endl;
                    result *= pow(key, val);
                }

                // Special case: if no factors found, GCD is 1
                if (result == 0)
                    cout << "The GCD of the two numbers is : 1" << endl;
                else
                    cout << "The GCD of the two numbers is : " << result << endl;
            }
        }
        else if (gcdlcm == "LCM")
        {
            if (num1 == 0 || num2 == 0)
            {
                cout << "0" << endl;
            }
            else
            {
                // For LCM, take maximum exponent for each prime
                for (auto &[key, val1] : number1)
                {
                    sum[key] = val1;
                }
                for (auto &[key, val2] : number2)
                {
                    if (sum[key] < val2)
                    {
                        sum[key] = val2;
                    }
                }

                // Multiply primes^exponent together
                for (const auto &[key, val] : sum)
                {
                    cout << "Number " << key << " exist " << val << " times." << endl;
                    result *= pow(key, val);
                }
                cout << "The LCM of the two numbers is : " << result << endl;
            }
        }
        else
        {
            // If user typed something wrong, ask again
            cout << "Please enter GCD or LCM and use capital letters!" << endl;
            goto start;
        }
    }
}
