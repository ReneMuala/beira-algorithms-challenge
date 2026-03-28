//ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

int extract_smallest_date(const std::string& line) {
	int smallest = -1;
	const int size = 2 + 1 + 2 + 1 + 4;
	for (int i = 0; i < line.size() - size; i++) {
		string candidate = line.substr(i, size);
		if(candidate[2] == '/' && candidate[5] == '/') {
			int val = atoi(candidate.substr(0, 2).c_str()) + 
				atoi(candidate.substr(3, 2).c_str()) * 30 + 
				atoi(candidate.substr(6, 5).c_str()) * 365;
			if(smallest == -1 || val < smallest) {
				smallest = val;
			}
		}
	}
	return smallest;
}

struct count_pair {
	std::string str;
	int count;
};

void add_count(std::vector<count_pair>& counts, const std::string& str)
{
	for(int i = 0; i < counts.size(); i++) {
		if(counts[i].str == str) {
			counts[i].count++;
			return;
		}
	}
	counts.push_back({ str, 1 });
}

std::string most_repeated_string(std::string line) {
	std::vector<count_pair> counts;
	std::string current = "";
	for(int i = 0; i < line.size(); i++) {
		if (iswalpha(line[i])) {
			current += line[i];
		}
		else if (not current.empty() or i+1 == line.size()) {
			add_count(counts, current);
			current = "";
		}
	}
	count_pair count_pair = { "", -1 };
	for (auto& count : counts) {
		if (count_pair.count == -1 || count_pair.count <= count.count) {
			count_pair.str = count.str;
			count_pair.count = count.count;
		}
	}
	return count_pair.str;
}


#define VECTOR_DATA \
"Foi em 10/12/1948 que os direitos humanos foram proclamados, solenemente proclamados, mas foi apenas em 16/12/1966 que os pactos internacionais os tornaram, juridicamente os tornaram, vinculativos para as nações.",\
"Desde 04/10/1957, a humanidade olha para o céu de forma diferente, completamente diferente, pois foi nesse dia que o Sputnik riscou, pioneiramente riscou, o espaço, até que 20/07/1969 o homem pisou, finalmente pisou, na Lua."\
"Em 08/05/1945, a Europa respirou, coletivamente respirou, aliviada, encerrando o que 01/09/1939 havia desencadeado, tragicamente desencadeado, mergulhando o mundo inteiro em escuridão.",\
"Foi em 28/06/1914 que um tiro ecoou, fatalmente ecoou, em Sarajevo, desencadeando o que só em 11/11/1918 terminaria, silenciosamente terminaria, deixando milhões de vidas, para sempre perdidas, pelo caminho.",\
"Quando 06/08/1945 amanheceu sobre Hiroshima, a humanidade cruzou, irreversivelmente cruzou, uma linha, confirmando três dias depois, em 09/08/1945, que o pior do engenho humano podia, cruelmente podia, destruir cidades inteiras em segundos.",\
"Em 25/04/1953, Watson e Crick revelaram, espantosamente revelaram, a estrutura do ADN, abrindo um caminho que em 26/06/2000 culminou, gloriosamente culminou, no mapeamento completo do genoma humano.",\
\
"Desde 12/04/1961, quando Gagarin voou, corajosamente voou, além da atmosfera, a humanidade nunca mais foi, jamais voltou a ser, a mesma que antes de 04/10/1957 sequer sonhava, timidamente sonhava, chegar tão longe.",\
\
"Foi em 09/11/1989 que o Muro de Berlim caiu, finalmente caiu, enterrando o que 13/08/1961 havia erguido, friamente erguido, dividindo famílias, separando vidas, por quase três décadas inteiras.",\
\
"Quando 11/03/2020 a OMS declarou, oficialmente declarou, pandemia, o mundo parou, abruptamente parou, tal como havia parado antes, dolorosamente parado, em 01/01/1918, quando a gripe espanhola começou, silenciosamente começou, a ceifar milhões de vidas.",\
\
"Em 15/03/1493, Colombo regressou, triunfantemente regressou, à Europa, mudando o mundo que havia partido em 03/08/1492, para sempre mudando, ao ligar dois mundos que jamais, em toda a eternidade, se haviam encontrado antes.",



int main() {
	auto start = std::chrono::steady_clock::now();
	std::vector<std::string> lines = {
		VECTOR_DATA
	};
	for(int i = 0; i < lines.size() - 1; i++) {
		int smallest_i = extract_smallest_date(lines[i]);
		int smallest_j = extract_smallest_date(lines[i + 1]);
		if(smallest_i != -1 && smallest_j != -1) {
			if(smallest_i > smallest_j) {
				std::string temp = lines[i];
				lines[i] = lines[i + 1];
				lines[i + 1] = temp;
				i = -1;
			}
		}
	}
	for(auto& line : lines) {
		std::cout << line << std::endl;
	}
	std::string lastest = lines[lines.size() - 1];
	std::cout << most_repeated_string(lastest) << std::endl;
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;
}
