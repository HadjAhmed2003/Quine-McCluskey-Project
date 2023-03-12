#include<bits/stdc++.h>
using namespace std;
bool isValidExpression(string expression, vector<string>& terms, vector<string>& variables){
    string current_minterm; 
    for(int i =0; i<expression.length(); i++){
        if(expression[i]!='\'' && expression[i]!='+' && !isalpha(expression[i])){
            return false;
        }
        else if(i==expression.length()-1){
            string temp_variable = "";
            temp_variable += expression[i];
            if(find(variables.begin(), variables.end(), temp_variable)==variables.end()){
                variables.push_back(temp_variable); 
            } 
            current_minterm +=temp_variable; 
            if(find(terms.begin(), terms.end(), current_minterm)==terms.end()){
                terms.push_back(current_minterm);
            } 
        }else if(isalpha(expression[i]) && expression[i+1]=='+'){
            string temp_variable = "";
            temp_variable += expression[i];
            if(find(variables.begin(), variables.end(), temp_variable)==variables.end()){
                variables.push_back(temp_variable); 
            } 
            current_minterm +=temp_variable; 
            if(find(terms.begin(), terms.end(), current_minterm)==terms.end()){
                terms.push_back(current_minterm);
            } 
        }
        else if(expression[i]=='+' && terms.size()==0){
            return false;
        }else if(expression[i] == '\'' && (i == 0||!isalpha(expression[i-1]))){
            return false;
        }else if(expression[i]=='+' && terms.size()!=0){
            if(find(terms.begin(), terms.end(), current_minterm)==terms.end()){
                terms.push_back(current_minterm);
            } 
            current_minterm = ""; 
        }else if(isalpha(expression[i]) && expression[i+1]=='\''){
            string temp_variable = "";
            temp_variable += expression[i];
            if(find(variables.begin(), variables.end(), temp_variable)==variables.end()){
                variables.push_back(temp_variable); 
            }
            temp_variable += expression[i+1];
            current_minterm +=temp_variable; 
            if(find(terms.begin(), terms.end(), current_minterm)==terms.end() && i==expression.length()-2){
                terms.push_back(current_minterm);
            } 
            i++;  
        }else{
            string temp_variable = "";
            temp_variable += expression[i];
            if(find(variables.begin(), variables.end(), temp_variable)==variables.end()){
                variables.push_back(temp_variable); 
            } 
            current_minterm +=temp_variable; 
        }
    }
    return true; 
}

void printTruthTable(const vector<string>& terms, vector<string> variables,vector<string>& binary_minterms, vector<int>& decimal_minterms) {
    int n = variables.size();
    int numRows = pow(2, n);
    sort(variables.begin(), variables.end());
    for (int i = 0; i < n; i++) {
        cout << variables[i] << "\t";
    }
    cout << "Output\n";
    for (int i = 0; i < n; i++) {
        cout << "-\t";
    }
    cout << "------\n";
    string PoS = ""; 
    string SoP = ""; 
    for (int i = 0; i < numRows; i++) {
        vector<bool> inputs;
        string temp_binary_minterm = "";
        for (int j = 0; j <n; j++){
            inputs.push_back((i >> j) & 1);
        }
        reverse(inputs.begin(), inputs.end());
        for(int j=0; j<n; j++){
            cout << inputs[j] << "\t";
            if(inputs[j]){
                temp_binary_minterm += "1"; 
            }else{
                temp_binary_minterm += "0"; 
            }
        }
        bool output = false;
        for (int j = 0; j < terms.size(); j++) {

            bool value = true;
            for(int z=0; z<terms[j].size();z++){
                for (int k = 0; k < n; k++) {
                    if (terms[j][z] == variables[k][0] && terms[j][z+1]!='\'') {
                        value &= inputs[k];
                    } else if (terms[j][z] == (variables[k][0]) && terms[j][z+1]=='\'') {
                        value &= !inputs[k];
                        z++; 
                    }
                }
            }
            output |= value;
        }
        string temp_minterm = "";
        string temp_maxterm = "(";
        for(int j=0; j<n; j++){
            if(inputs[j]==0){
                temp_maxterm+= (variables[j] + "+");
                temp_minterm+= (variables[j] + "\'");
            }else{
                temp_maxterm+= (variables[j] + "\'"+ "+");
                temp_minterm+= (variables[j]);
            }
        }
        if(output){
            SoP += (temp_minterm + "+");
            binary_minterms.push_back(temp_binary_minterm);
            decimal_minterms.push_back(i);
        }else{
            PoS += (temp_maxterm);
            PoS[PoS.length()-1]=')';
        }
        cout << output << "\n";
    }
    SoP[SoP.length()-1]=' ';
    cout << "\n\n";
    cout << "Canonical SoP: " << SoP << endl;
    cout << "Canonical PoS: " << PoS << endl;  
}
//Youssef
set<int> makeSet(int num) {
    return set<int>({num});
}

set<set<int>> vectorToSet(vector<int>& vec) {
    set<set<int>> result;
    for (int num : vec) {
        result.insert(makeSet(num));
    }
    return result;
}

//detect the number of variables in boolean function
int num_of_variables(vector<int> minterms) {
    int max = 0;
    for (int i = 0; i < minterms.size(); i++) {
        if (minterms[i] > max) {
            max = minterms[i];
        }
    }
    int num_of_bits = 0;
    while (max > 0) {
        max = max / 2;
        num_of_bits++;
    }
    return num_of_bits;
}

//convert minterms from decimal to binary
vector<string> minterms_to_binary(vector<int> minterms, int v) {
    vector<string> binary;
    for (int i = 0; i < minterms.size(); i++) {
        string temp = "";
        int num = minterms[i];
        for (int j = 0; j < v; j++) {
            temp += to_string(num % 2);
            num /= 2;
        }
        reverse(temp.begin(), temp.end());
        binary.push_back(temp);
    }
    return binary;
}
template <typename T>
void print(vector<T> vec) {
    for (auto x : vec) {
        cout << x<<", ";
    }
    cout << '\n';
}

template <typename T>
void print(vector<vector<T>> vec) {
    for (auto row : vec) {
        for (auto x : row) {
            cout << x << ", ";
        }
        cout << '\n';
    }
    cout << '\n';
}

void print(set<set<int>> s) {
    for (auto row : s) {
        cout << "{ ";
        for (auto el : row) {
            cout << el << ", ";
        }
        cout << "} ";
    }
    cout << '\n';
}

void print(set<string> s) {
    for (auto x : s) {
        cout << x << ", ";
    }
    cout << '\n';
}
vector<vector<string>> group_minterms(vector<string> minterms)
{
    vector<vector<string>> minterm_groups;
    int minterm_length = minterms[0].length();
    int minterm_count = minterms.size();
    int minterm_ones_count = 0;
    //loop over possible indices of the List of groups (e.g., index i means Group of i 1s)
    for (int i = 0; i <= minterm_length; i++)
    {
        vector<string> minterm_group;

        //loop over all minterms (ms)
        for (int j = 0; j < minterm_count; j++)
        {
            //store # of 1s in current m
            minterm_ones_count = 0;

            //count # of 1s in each m
            for (int k = 0; k < minterm_length; k++)
            {
                if (minterms[j][k] == '1')
                {
                    minterm_ones_count++;
                }
            }

            //choose m if # of 1s == i
            if (minterm_ones_count == i)
            {
                minterm_group.push_back(minterms[j]);
            }
        }
        minterm_groups.push_back(minterm_group);
    }
    return minterm_groups;
}

//exmaple input x010x  --> 4, 5, 20, 21
set<int> to_decimal_set(string s)
{
    set<int> result;
    if (s.find('x') == string::npos)
    {
        result.insert(stoi(s, nullptr, 2));
        return result;
    }
    else
    {
        string s1 = s;
        string s2 = s;
        s1.replace(s1.find('x'), 1, "0");
        s2.replace(s2.find('x'), 1, "1");
        set<int> result1 = to_decimal_set(s1);
        set<int> result2 = to_decimal_set(s2);
        result.insert(result1.begin(), result1.end());
        result.insert(result2.begin(), result2.end());
        return result;
    }
}

int to_decimal(string binaryString)
{
    int decimal = 0;
    int power = 0;
    for (int i = binaryString.length() - 1; i >= 0; i--)
    {
        if (binaryString[i] == '1')
        {
            decimal += pow(2, power);
        }
        power++;
    }
    return decimal;
}

void remove_dubplicates(vector<string>& v)
{
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}
void compare(vector<vector<string>>& minterms_group, set<set<int>>& implicants, set<string>& implicants_string, set<string>& final_prime_implicants_str,set<set<int>>& final_prime_implicants) {
    vector<string> result;
    set<set<int>> combined;
    set<string> combined_str;
    //loop over 1_count_based groups
    for (int i = 0; i < minterms_group.size() - 1; i++) {
        //loop over minterms of current goup
        for (int j = 0; j < minterms_group[i].size(); j++) {
            //loop number of times equal to the number of minterms in the next 1_count_based group
            for (int k = 0; k < minterms_group[i + 1].size(); k++) {
                //stores nmber of different bits
                int count = 0;
                //this loops constant number of times equal to the number of variables in boolean function
                for (int l = 0; l < minterms_group[i][j].size(); l++) {
                    if (minterms_group[i][j][l] != minterms_group[i + 1][k][l]) {
                        count++;
                    }
                }
                if (count == 1) {
                    string temp = "";
                    set<int> a = to_decimal_set(minterms_group[i][j]);
                    set<int> b = to_decimal_set(minterms_group[i + 1][k]);
                    implicants.erase(a);
                    implicants.erase(b);
                    implicants_string.erase(minterms_group[i][j]);
                    implicants_string.erase(minterms_group[i + 1][k]);
                    a.insert(b.begin(), b.end());

                    combined.insert(a);

                    for (int l = 0; l < minterms_group[i][j].size(); l++) {
                        if (minterms_group[i][j][l] != minterms_group[i + 1][k][l]) {
                            temp += "x";
                        }
                        else {
                            temp += minterms_group[i][j][l];
                        }
                    }
                    combined_str.insert(temp);
                    result.push_back(temp);
                }
            }
        }
    }

    final_prime_implicants.insert(implicants.begin(), implicants.end()); //not erased minterms
    final_prime_implicants_str.insert(implicants_string.begin(), implicants_string.end());
    implicants = combined; //combined implicants for the use of next list in the form { {1,3}, {3, 5} }
    implicants_string = combined_str;
    if (implicants.size() <= 1) {
        if (implicants.size() == 1) {
            final_prime_implicants.insert(implicants.begin(), implicants.end());
            final_prime_implicants_str.insert(implicants_string.begin(), implicants_string.end());
        }
        return;
    }
        
    remove_dubplicates(result);
    minterms_group = group_minterms(result);

    return;
}

void generate_final_prime_implicants(vector<vector<string>>& minterms_group, set<set<int>>& implicants, set<string>& implicants_string, set<string>& final_prime_implicants_str, set<set<int>>& final_prime_implicants) {
    if (implicants.size() <= 1)
        return;
    compare(minterms_group, implicants, implicants_string, final_prime_implicants_str, final_prime_implicants);
    generate_final_prime_implicants(minterms_group, implicants, implicants_string, final_prime_implicants_str, final_prime_implicants);
}
int main(){
    vector<string> terms; 
    vector<string> variables;
    vector<string> binary_minterms;
    vector<int> decimal_minterms;
    string expression; 
    cin >> expression; 
    isValidExpression(expression,terms,variables);
    printTruthTable(terms,variables,binary_minterms,decimal_minterms);
        //Youssef
    set<set<int>> implicants = vectorToSet(decimal_minterms);
    vector<vector<string>> minterms_group = group_minterms(binary_minterms);
    set<string> implicants_str(binary_minterms.begin(), binary_minterms.end());
    set<set<int>> final_prime_implicants;
    set<string> final_prime_implicants_str;

    generate_final_prime_implicants(minterms_group, implicants, implicants_str, final_prime_implicants_str, final_prime_implicants);
    cout<<"Prime Implicants represented in binary:\n";
    print(final_prime_implicants_str);
    cout<<"Prime Implicants represented by the minterms covered\n";
    print(final_prime_implicants);
    return 0; 
}
