#include "Validation.h"

int Validation::ValidateIntInput(string prompt, int min, int max)
{
    int value = 0;
    while (true) {
		cout << prompt;
        if (!(cin >> value))
        {
            cout << "Invalid number. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (value < min || value > max)
        {
            cout << "Input must be between " << min << " and " << max << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

}

string Validation::ValidateStringInput(string prompt)
{
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (value.empty())
        {
            cout << "Input cannot be empty. Try again.\n";
            continue;
        }
        return value;
	}
}

float Validation::ValidateFloatInput(string prompt, float min, float max)
{
    float value = 0.0f;
    while (true) {
        cout << prompt;
        if (!(cin >> value))
        {
            cout << "Invalid number. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (value < min || value > max)
        {
            cout << "Input must be between " << min << " and " << max << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
	}
}

ItemType Validation::ValidateItemTypeInput(string prompt)
{
	int choice = -1;
    while (true) {
        cout << prompt;
        if (!(cin >> choice))
        {
            cout << "Invalid number. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice < 1 || choice > 4)
        {
            cout << "Input must be between 0 and 3." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return static_cast<ItemType>(choice);
    }
}

bool Validation::ValidateFilePath(const string& path)
{
    if (path.empty())
    {
        cout << "File path cannot be empty. Try again." << endl;
        return false;
	}

	size_t invalidChars = path.find_last_of('.');
    if (invalidChars == string::npos) {
        cout<< "File path must contain a file extension. Try again." << endl;
		return false;
    }
	string fileExtension = path.substr(invalidChars);
    for(char& c : fileExtension) {
		c = static_cast<char>(tolower(c));
	}

    return fileExtension == ".txt";
}
