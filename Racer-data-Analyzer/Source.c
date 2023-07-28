#include <stdio.h>
#include <string.h>

struct default_pretekar {
	char meno[30];
	char priezvisko[30];
	char mf[5];
	int year;
	char model[20];
	float laps[5];
	float bestLap;
	int cisKol;
	float worstLap;
};

struct default_pretekar pretekar[20];

void fastest_slowest() {

	int n = 0;

	while (strlen(pretekar[n].meno) != 0) {
		float fastest, slowest;
		fastest = slowest = pretekar[n].laps[0];
		for (int j = 0; j < sizeof(pretekar[n].laps) / sizeof(pretekar[n].laps[0]); j++) {
			if (pretekar[n].laps[j] > slowest)
				slowest = pretekar[n].laps[j];
				pretekar[n].worstLap = slowest;

			if (pretekar[n].laps[j] < fastest)
				fastest = pretekar[n].laps[j];
				pretekar[n].bestLap = fastest;
		}

		for (int i = 0; i < sizeof(pretekar[n].laps) / sizeof(pretekar[n].laps[0]); i++) {
			if (pretekar[n].bestLap == pretekar[n].laps[i]) {
				pretekar[n].cisKol = i + 1;
			}
		}

		n++;

	}
}

void reading_file() {
	FILE* fp = fopen("tabulka.csv", "r");

	if (!fp) {
		printf("error occured");
	}

	char buff[1024];
	int field_count = 0;
	int row_count = 0;
	int i = 0;

	memset(pretekar, 0, sizeof(pretekar));

	while (fgets(buff, 1024, fp)) {
		field_count = 0;
		row_count++;
		char* field = strtok(buff, ";");
		while (field) {
			if ((field_count) == 0) {
				char m[30], p[30];
				sscanf(field, "%s %s", &m, &p);
				strcpy(pretekar[i].meno, m);
				strcpy(pretekar[i].priezvisko, p);
			}
			if ((field_count) == 1) {
				char k[2] = "m";
				char t[2] = "f";
				if (*field == *k) {
					field = "muz";
					strcpy(pretekar[i].mf, field);
				}
				else {
					field = "zena";
					strcpy(pretekar[i].mf, field);
				}
			}
			if ((field_count) == 2) {
				pretekar[i].year = atoi(field);
			}
			if ((field_count) == 3) {
				strcpy(pretekar[i].model, field);
			}
			if ((field_count) == 4) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[0] = f;
			}
			if ((field_count) == 5) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[1] = f;
			}
			if ((field_count) == 6) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[2] = f;
			}
			if ((field_count) == 7) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[3] = f;
			}
			if ((field_count) == 8) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[4] = f;
			}

			field = strtok(NULL, ";");
			field_count++;

		}
		i++;
	}
	fastest_slowest();
	fclose(fp);

}

void sum() {

	reading_file();

	int n = 0;	
	while (strlen(pretekar[n].meno) != 0) {
		printf("%s %s, nar. %d, %s, Automobil: %s\n", pretekar[n].meno, pretekar[n].priezvisko, pretekar[n].year, pretekar[n].mf, pretekar[n].model);
		printf("Casy Okruhov: %.3lf; %.3lf; %.3lf; %.3lf; %.3lf\n", pretekar[n].laps[0], pretekar[n].laps[1], pretekar[n].laps[2], pretekar[n].laps[3], pretekar[n].laps[4]);
		printf("............\n");
		n++;
	}
	
	
	return 0;

}

void driver() {
	reading_file();
	char priezvisko[30];
	printf("napiste priezvisko jazdca: ");
	scanf("%s", priezvisko);
	int n = 0, b = 0, pret_num = 0;
	float priemarne;
	int t_f = 0;
	while (strlen(pretekar[n].meno) != 0) {
		if (strcmp(pretekar[n].priezvisko, priezvisko) == 0) {
			priemarne = (pretekar[n].laps[0] + pretekar[n].laps[1] + pretekar[n].laps[2] + pretekar[n].laps[3] + pretekar[n].laps[4]) / 5;
			printf("%s %s\n", pretekar[n].meno, pretekar[n].priezvisko);
			printf("nar. %d, %s\n", pretekar[n].year, pretekar[n].mf);
			printf("Automobil: %s\n", pretekar[n].model);
			printf("\n");
			printf("Casy Okruhov: %.3lf; %.3lf; %.3lf; %.3lf; %.3lf\n", pretekar[n].laps[0], pretekar[n].laps[1], pretekar[n].laps[2], pretekar[n].laps[3], pretekar[n].laps[4]);
			printf("\n");
			printf("Najlepsie kolo: %.3lf\n", pretekar[n].bestLap);
			printf("Najhorsie kolo: %.3lf\n", pretekar[n].worstLap);
			printf("Priemerne kolo: %.3lf\n", priemarne);
			pret_num++;
			t_f = 1;
		}
		n++;
	}
	if (t_f == 0) {
		printf("Neexistuje pretekar s tymto priezviskom\n");
	}
}

void lap() {
	reading_file();
	int n = 0;
	int j = 0;
	float best = pretekar[0].bestLap;
	while (strlen(pretekar[n].meno) != 0) {
		if (pretekar[n].bestLap < best) {
			best = pretekar[n].bestLap;
			j = n;
		}
		n++;
	}
	printf("Najlepsie kolo: %.3lf\n", best);
	printf("Jazdec: %s %s\n", pretekar[j].meno, pretekar[j].priezvisko);
	printf("cislo kola: %d\n", pretekar[j].cisKol);

}

void gender() {
	reading_file();
	char pohlavie[5];
	char k[2] = "m", muz[5] = "muz";
	char t[2] = "f", zena[5] = "zena";
	printf("napiste gedner: ");
	scanf("%s", &pohlavie);
	printf("\n");
	if (*pohlavie == *k) {
		strcpy(pohlavie, "muz");

	}
	else {
		strcpy(pohlavie, "zena");
	}	
	int n = 0;
	int j = 0;
	float best = 100.0;
	while (strlen(pretekar[n].meno) != 0) {
		if (*pretekar[n].mf == *pohlavie) {
			if (pretekar[n].bestLap < best) {
				best = pretekar[n].bestLap;
				j = n;
			}
		}
		n++;		
	}
	printf("Najlepsie kolo: %.3lf\n", best);
	printf("Jazdec: %s %s\n", pretekar[j].meno, pretekar[j].priezvisko);
	printf("Cislo Kola: %d", pretekar[j].cisKol);
}

void brand() {
	reading_file();
	char b[10] = "bugatti", f[10] = "ferrari", h[10] = "honda", p[10] = "porsche";
	int n = 0;
	float bestB = 100.00;
	float bestF = 100.00;
	float bestH = 100.00;
	float bestP = 100.00;

	while (strlen(pretekar[n].meno) != 0) {
		if (strcmp(pretekar[n].model, b) == 0 && pretekar[n].bestLap < bestB) {
			bestB = pretekar[n].bestLap;
			printf("Znacka: %s\n", b);
			printf("Najlepsie kolo: %.3lf\n", bestB);
			printf("Jazdec: %s %s\n", pretekar[n].meno, pretekar[n].priezvisko);
			printf("Cislo kola: %d\n", pretekar[n].cisKol);
			printf("\n");			
		}
		else if (strcmp(pretekar[n].model, f) == 0 && pretekar[n].bestLap < bestF) {
			bestF = pretekar[n].bestLap;
			printf("Znacka: %s\n", f);
			printf("Najlepsie kolo: %.3lf\n", bestF);
			printf("Jazdec: %s %s\n", pretekar[n].meno, pretekar[n].priezvisko);
			printf("Cislo kola: %d\n", pretekar[n].cisKol);
			printf("\n");

		}
		else if (strcmp(pretekar[n].model, h) == 0 && pretekar[n].bestLap < bestH) {
			bestH = pretekar[n].bestLap;
			printf("Znacka: %s\n", h);
			printf("Najlepsie kolo: %.3lf\n", bestH);
			printf("Jazdec: %s %s\n", pretekar[n].meno, pretekar[n].priezvisko);
			printf("Cislo kola: %d\n", pretekar[n].cisKol);
			printf("\n");
		}
		else if (strcmp(pretekar[n].model, p) == 0 && pretekar[n].bestLap < bestP) {
			bestP = pretekar[n].bestLap;
			printf("Znacka: %s\n", p);
			printf("Najlepsie kolo: %.3lf\n", bestP);
			printf("Jazdec: %s %s\n", pretekar[n].meno, pretekar[n].priezvisko);
			printf("Cislo kola: %d\n", pretekar[n].cisKol);
			printf("\n");
		}


		n++;
	}
}

void year() {
	reading_file();
	int n = 0, j = 0, y;
	float best = 100.00;
	printf("zadajte rok narodenia vo formate 'YYYY' \n");
	scanf("%d", &y);

	while (strlen(pretekar[n].meno) != 0) {
		if (pretekar[n].year < y && pretekar[n].bestLap < best) {
			
			best = pretekar[n].bestLap;
			j = n;
		}
		n++;
	}

	printf("\n");
	printf("%s %s\n", pretekar[j].meno, pretekar[j].priezvisko);
	printf("nar. %d\n", pretekar[j].year);
	printf("Najlepsie kolo: %.3lf\n", pretekar[j].bestLap);
	printf("Cislo Kola: %d", pretekar[j].cisKol);
	printf("\n");
	
}

void average() {
	reading_file();
	int n = 0, j = 0;
	float average = 0;
	float bestAverage = 1000;
	while (strlen(pretekar[n].meno) != 0) {
		for (int i = 0; i < sizeof(pretekar[n].laps) / sizeof(pretekar[n].laps[0]); i++) {
			average += pretekar[n].laps[i];
			if (i == 4) {
				average = average / 5;
				printf("%s %s - %.3lf\n", pretekar[n].meno, pretekar[n].priezvisko, average);
				if (average <= bestAverage) {
					bestAverage = average;
					j = n;
				}
			}
		}
		n++;
	}
	printf("\n");
	printf("Najlepsie: \n");
	printf("%s %s - %.3lf\n", pretekar[j].meno, pretekar[j].priezvisko, bestAverage);
}

void under() {
	reading_file();
	float cas;
	printf("napiste cas kola: ");
	scanf("%f", &cas);
	int n = 0;
	while (strlen(pretekar[n].meno) != 0) {
		float koly[5] = {0};
		int pocet_kolov = 0;
		for (int i = 0; i < sizeof(pretekar[n].laps) / sizeof(pretekar[n].laps[0]); i++) {
			if (pretekar[n].laps[i] < cas) {
				pocet_kolov++;
				koly[i] = pretekar[n].laps[i];
			}			
		}
		int j = 0;

		if (pocet_kolov != 0) {
			printf("%s %s - ", pretekar[n].meno, pretekar[n].priezvisko);
			printf("%d kola - ", pocet_kolov);
			for (int j = 0; j < 5; j++) {
				if (koly[j] != 0) {
					printf(" (%d) %.3lf, ", j + 1, koly[j]);
				}

			}
		}


		printf("\n");
		n++;
	}
}

void change() {
	FILE* fp = fopen("tabulka.csv", "r");

	if (!fp) {
		printf("error occured");
	}

	char buff[1024];
	int field_count = 0;
	int row_count = 0;
	int i = 0, n = 0;

	while (fgets(buff, 1024, fp)) {
		field_count = 0;
		row_count++;
		char* field = strtok(buff, ";");
		while (field) {
			if ((field_count) == 0) {
				char m[30], p[30];
				sscanf(field, "%s %s", &m, &p);
				strcpy(pretekar[i].meno, m);
				strcpy(pretekar[i].priezvisko, p);
			}
			if ((field_count) == 1) {
				char k[2] = "m";
				char t[2] = "f";
				if (*field == *k) {
					field = "muz";
					strcpy(pretekar[i].mf, field);
				}
				else {
					field = "zena";
					strcpy(pretekar[i].mf, field);
				}
			}
			if ((field_count) == 2) {
				pretekar[i].year = atoi(field);
			}
			if ((field_count) == 3) {
				strcpy(pretekar[i].model, field);
			}
			if ((field_count) == 4) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[0] = f;
			}
			if ((field_count) == 5) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[1] = f;
			}
			if ((field_count) == 6) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[2] = f;
			}
			if ((field_count) == 7) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[3] = f;
			}
			if ((field_count) == 8) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[4] = f;
			}

			field = strtok(NULL, ";");
			field_count++;

		}
		i++;
	}
	fclose(fp);

	char changed_driver[30];
	printf("zdajte priezvisko: ");
	scanf("%s", &changed_driver);
	int cislo_kola = 0;
	printf("prosim zadajte cislo kola: ");
	scanf("%d", &cislo_kola);
	float newTime = 0;
	printf("prosim zadajte novy cas kola: ");
	scanf("%f", &newTime);

	FILE* changed = fopen("tabulka.csv", "w");


	while (strlen(pretekar[n].meno) != 0) {
		if (strcmp(pretekar[n].priezvisko, changed_driver) != 0) {
			fprintf(changed, "%s %s;%s;%d;%s;%.3lf;%.3lf;%.3lf;%.3lf;%.3lf\n", pretekar[n].meno, pretekar[n].priezvisko, pretekar[n].mf, pretekar[n].year,
				pretekar[n].model, pretekar[n].laps[0], pretekar[n].laps[1], pretekar[n].laps[2], pretekar[n].laps[3], pretekar[n].laps[4]);
			//printf("%s %s, nar. %d, %s, Automobil: %s\n", pretekar[n].meno, pretekar[n].priezvisko, pretekar[n].year, pretekar[n].mf, pretekar[n].model);
			//printf("Casy Okruhov: %.3lf; %.3lf; %.3lf; %.3lf; %.3lf\n", pretekar[n].laps[0], pretekar[n].laps[1], pretekar[n].laps[2], pretekar[n].laps[3], pretekar[n].laps[4]);
		}
		else {
			pretekar[n].laps[cislo_kola - 1] = newTime;
			fprintf(changed, "%s %s;%s;%d;%s;%.3lf;%.3lf;%.3lf;%.3lf;%.3lf\n", pretekar[n].meno, pretekar[n].priezvisko, pretekar[n].mf, pretekar[n].year,
				pretekar[n].model, pretekar[n].laps[0], pretekar[n].laps[1], pretekar[n].laps[2], pretekar[n].laps[3], pretekar[n].laps[4]);
		}
		n++;
	}

	fclose(changed);

}

void newdriver() {
	char name[30];
	char surname[30];
	char mf[5];
	int nar;
	char car[30];
	float lap1;
	float lap2;
	float lap3;
	float lap4;
	float lap5;
	printf("prosim zadajte meno a priezvisko jazdca: ");
	scanf("%s %s", &name, &surname);
	//printf("mp = %s %s", name, surname);
	printf("prosim zadajte pohlavie jazdca: ");
	scanf("%s", &mf);
	//printf("mf = %s", mf);
	printf("prosim zadajte rok narodenia jazdca: ");
	scanf("%d", &nar);
	//printf("nar = %d", nar);
	printf("prosim zadajte automobil jazdca (porsche, bugatti, honda alebo ferrari): ");
	scanf("%s", &car);
	printf("prosim zadajte cas kolov v formate - YY.XXX;YY.XXX;YY.XXX;YY.XXX;YY.XXX:  \n");
	scanf("%f;%f;%f;%f;%f", &lap1, &lap2, &lap3, &lap4, &lap5);
	FILE* fp = fopen("tabulka.csv", "a+");
	fprintf(fp, "%s %s;%s;%d;%s;%.3lf;%.3lf;%.3lf;%.3lf;%.3lf\n", name, surname, mf, nar, car, lap1, lap2, lap3, lap4, lap5);	
	fclose(fp);
	sum();

}

void rmdriver() {

	FILE* fp = fopen("tabulka.csv", "r");

	if (!fp) {
		printf("error occured");
	}

	char buff[1024];
	int field_count = 0;
	int row_count = 0;
	int i = 0, n = 0;

	while (fgets(buff, 1024, fp)) {
		field_count = 0;
		row_count++;
		char* field = strtok(buff, ";");
		while (field) {
			if ((field_count) == 0) {
				char m[30], p[30];
				sscanf(field, "%s %s", &m, &p);
				strcpy(pretekar[i].meno, m);
				strcpy(pretekar[i].priezvisko, p);
			}
			if ((field_count) == 1) {
				char k[2] = "m";
				char t[2] = "f";
				if (*field == *k) {
					field = "muz";
					strcpy(pretekar[i].mf, field);
				}
				else {
					field = "zena";
					strcpy(pretekar[i].mf, field);
				}
			}
			if ((field_count) == 2) {
				pretekar[i].year = atoi(field);
			}
			if ((field_count) == 3) {
				strcpy(pretekar[i].model, field);
			}
			if ((field_count) == 4) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[0] = f;
			}
			if ((field_count) == 5) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[1] = f;
			}
			if ((field_count) == 6) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[2] = f;
			}
			if ((field_count) == 7) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[3] = f;
			}
			if ((field_count) == 8) {
				float f;
				sscanf(field, "%f", &f);
				pretekar[i].laps[4] = f;
			}

			field = strtok(NULL, ";");
			field_count++;

		}
		i++;
	}	

	fclose(fp);

	char vimazeni_jazdec[30];
	printf("prosim zadajte priezvisko jazdca: ");
	scanf("%s", vimazeni_jazdec);
	

	FILE* vimazeni = fopen("tabulka.csv", "w");
	

	
	while (strlen(pretekar[n].meno) != 0) {
		if (strcmp(pretekar[n].priezvisko, vimazeni_jazdec) != 0) {
			fprintf(vimazeni, "%s %s;%s;%d;%s;%.3lf;%.3lf;%.3lf;%.3lf;%.3lf\n", pretekar[n].meno, pretekar[n].priezvisko, pretekar[n].mf, pretekar[n].year,
				pretekar[n].model, pretekar[n].laps[0], pretekar[n].laps[1], pretekar[n].laps[2], pretekar[n].laps[3], pretekar[n].laps[4]);
			//printf("%s %s, nar. %d, %s, Automobil: %s\n", pretekar[n].meno, pretekar[n].priezvisko, pretekar[n].year, pretekar[n].mf, pretekar[n].model);
			//printf("Casy Okruhov: %.3lf; %.3lf; %.3lf; %.3lf; %.3lf\n", pretekar[n].laps[0], pretekar[n].laps[1], pretekar[n].laps[2], pretekar[n].laps[3], pretekar[n].laps[4]);
		}
		else {
			printf("jazdec z menom '%s %s' bol vimazany\n", pretekar[n].meno, pretekar[n].priezvisko);
		}
		n++;
	}



	fclose(vimazeni);

	
}

void navigation() {
	char func_name;
	printf("zadajte pismeno: ");
	while (1) {
		scanf("%c", &func_name);
		printf("\n");
		switch (func_name) {
			case 's':
				sum();
				break;
			case 'd':
				driver();
				break;
			case 'l':
				lap();
				break;
			case 'g':
				gender();
				break;
			case 'b':
				brand();
				break;
			case 'y':
				year();
				break;
			case 'a':
				average();
				break;
			case 'u':
				under();
				break;
			case 'n':
				newdriver();
				break;
			case 'c':
				change();
				break;
			case 'r':
				rmdriver();
				break;
			case 'x':
				exit(1);
				break;
			default:
				printf("zadajte pismeno: ");
				break;
		}
	}
}

int main() {
	navigation();
	return 0;
}