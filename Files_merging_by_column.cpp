//Files_merging_by_column

/*
*--------------------------------------------------------------------------
*"The BEER-WARE LICENSE (Revision 01):
* <291486@fizyka.umk.pl> wrote this file. As long as you retain this notice you
* can do watever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a beer in return Jan Kaminski
*--------------------------------------------------------------------------
http://fizyka.umk.pl/~291486/Beer-ware
*/



#include <iostream>
#include <string>
#include <stack>
#include <fstream>



using namespace std;


int number_of_digits(int num){
    if(num==0) return 1;

    int i=0;
    while (num>0){
        num/=10;
        i++;
    }
    return i;
}

void files_merging(stack<string> pre,unsigned int min_index,unsigned int max_index,stack<string> after,unsigned int skipped_lines,int number_of_chars, bool with_tabs,int leading_zeros){

    //deklarowanie plikow
    fstream pliki[max_index-min_index+1];

    //otwieranie plikow
    for(int i=0;i<=max_index-min_index;++i){
        //budowa linku

        //proby poczatkow
        stack<string> tempPre  =pre;

        pliki[i].open("musi_nieistniec.txt",ios::in);
        while(!pliki[i].good()){
        if(pliki[i].is_open()) pliki[i].close();

            //proby koncow
            stack<string> tempAfter=after;

            while(!pliki[i].good()){
            if(pliki[i].is_open()) pliki[i].close();
                string link;

                link+=tempPre.top();

                int numer=i+min_index;

                //zera wiodace
                int templimit=number_of_digits(numer);
                for (int ii=0;ii<leading_zeros-templimit;++ii) {
                    cout<<leading_zeros-templimit<<endl;
                        link+='0';
                }

                //cyfra
                if(i>=99) link+= '0'+(numer/100)%10;
                if(i>= 9) link+= '0'+(numer/10) %10;
                          link+= '0'+ numer     %10;


                link+=tempAfter.top();
                tempAfter.pop();

                // .txt
                link+=".txt";
                pliki[i].open(link.c_str(),ios::in);
            }
            tempPre.pop();
        }

    }


    //pomijanie zbednych linijek
    {
        string line;
        for(int i=0;i<=max_index-min_index;++i){
            for(int ii=0;ii<skipped_lines;++ii){
                getline(pliki[i],line); //4 razy wczytuje puste linie dla kazdego z plikow, co przesuwa je na faktyczne dane
            }
        }
    }

    //inicjowanie wyjscia
    fstream plik_out("out.txt",ios::out);



    //zbieranie i ukladanie
        {
        string line;
        while(!pliki[0].eof()){  //"dopuki pierwszy plik sie nie skonczy" , zakladam, ze sa tego samego rozmiaru
            for(int i=0;i<=max_index-min_index;++i){
                getline(pliki[i],line);

                if(number_of_chars==-1){
                    plik_out<<line;
                }
                else if(number_of_chars==-2){
                    plik_out<<line.substr(0,line.size()/2+1) ;
                }
                else{
                    plik_out<<line.substr(0,number_of_chars) ; //wklej 6 pierwszych znakow linii pliku [i]
                }
                if(with_tabs) plik_out<<char(9); //char(9) == tab

            }
            plik_out<<endl; //enter po kazdym wpisaniu wszystkich linii z wszystkich plikow
        }
    }




    //zamykanie plikow
    cout<<"plik out.txt zostal utworzony poprawnie"<<endl;
    plik_out.close();

    for(int i=0;i<=max_index-min_index;++i){
        pliki[i].close();
    }
}

/*
void files_merging(stack<string> pre,unsigned int min_index,unsigned int max_index,stack<string> after){
    files_merging(pre , min_index , max_index , after , 0 );
}

void files_merging(stack<string> pre,unsigned int max_index,stack<string> after, int leading_zeros){
    files_merging(pre , 1 , max_index , after , leading_zeros );
}

void files_merging(stack<string> pre,unsigned int max_index,stack<string> after){
    files_merging(pre , 1 , max_index , after , 0 );
}

void files_merging(stack<string> pre,unsigned int max_index){
    stack<string> after;
    files_merging(pre , 1 , max_index , after , 0 );
}

void files_merging(unsigned int max_index,stack<string> after){
    stack<string> pre;
    files_merging(pre , 1 , max_index , after , 0 );
}

void files_merging(unsigned int max_index){
    stack<string> pre,after;
    files_merging(pre , 1 , max_index , after , 0 );
}

void files_merging(unsigned int min_index, unsigned int max_index){
    stack<string> pre,after;
    files_merging(pre , min_index , max_index , after , 0 );
}

void files_merging(unsigned int min_index, unsigned int max_index, int leading_zeros){
    stack<string> pre,after;
    files_merging(pre , min_index , max_index , after , leading_zeros );
}

*/









int main(){
    stack<string> pre , after;
    unsigned int min_index , max_index ,skipped_lines;
    int leading_zeros,number_of_chars;
    bool with_tabs;


    /*
    spec"
    pre - wrzuc wszystkie mozliwe przedrostki
    after - wrzuc wszystkie mozliwe... dorostki?
    min_index - minimalna liczba
    max_index - maksymalna liczba
    skipped_lines - niewazne linie w plikach
    leading_zeros - zera wiodace w numerowaniu
    number_of_chars - ilosc znakow na plik
        dodatkowe:
        -1 = calosc
        -2 = polowa z zaokrogleniem w gore;
    with_tabs - czy oddzielic tabami? (true/false)
    */


    //uwaga!, pusty wpis w pre i after tez sa wazne,
    //program wlaczy pierwszy plik ktory mu podpasuje dla kazdego numeru. Tylko jeden!

    /*
    pre.push("");
    after.push("");
    min_index=1;
    max_index=4;
    skipped_lines=4;
    leading_zeros=0;
    //number_of_chars=6; with_tabs=1;
    number_of_chars = -2; with_tabs = 0;
    */


    pre.push("");
    after.push("_100" );
    after.push("_1k"  );
    after.push("_10k" );
    after.push("_100k");
    after.push("_1M"  );
    min_index=1;
    max_index=4;
    skipped_lines=4;
    leading_zeros=0;
    //number_of_chars=6; with_tabs=1;
    number_of_chars = -2; with_tabs = 0;


    files_merging(pre , min_index , max_index , after ,skipped_lines, number_of_chars, with_tabs, leading_zeros );


    return 0;
}
