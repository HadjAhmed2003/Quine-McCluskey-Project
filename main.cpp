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

int main(){
    vector<string> terms; 
    vector<string> variables;
    vector<string> binary_minterms;
    vector<int> decimal_minterms;
    string expression; 
    cin >> expression; 
    isValidExpression(expression,terms,variables);
    printTruthTable(terms,variables,binary_minterms,decimal_minterms);
    return 0; 
}
