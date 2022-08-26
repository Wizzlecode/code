#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Company
{
	char name[100];
	char address[100];
	char area[100];
	struct Post* postHead;//element de la tete de liste chainée stages proposé par l'entreprise
	struct Company* next;//pointeur vers l'entreprise suivante
}Company;

typedef struct Student
{
	char name[50];
	struct Post* postHead;//element de la tete de liste chainée simple des stages postulés par l'eleve
	struct Student* next;//pointeur vers l'eleve suivant
}Student;

typedef struct Post //stage
{
	char name[100];
	struct Student* student;//l'eleve qui est accepte
	int status;//le statue: 0--non decide 1--accepte -1--refuse
	struct Post* next;//pointeur vers le stage suivant
}Post;


//variable globale
Company* compHead;//element de la tete de liste chainee simple de l'entreprise
Student* studHead;//element de la tete de liste chainee simple de l'eleve


//initialisation du système
void sysInit();
//menu principal
void home();
//pour saisir le choix pour le menu principal
void mainOption();
//case 1 gestion de compte d'entreprise
void compManage();

//cases de menu d'entreprise
//affichage de ce menu
void compMenu();
//pour saisir le choix pour le menu d'entreprise
int compOption();
//case1 creer un compte
void registeComp();
//case2 modifier des informations de base
void modifyCompBaseInfo();
//case3 modifier des informations de stage
void modifyCompPostInfo();
//affichage
void showAllCompPostInfo();
//supprimer une candidature
void delPostStud();
//affichage des informations des stages pour une entreprise
void showCompPostInfo(Company* comp);


void studManage();

void studMenu();

int studOption();

void registeStud();

void modifyStudBaseInfo();

void delApplication();

void addApplication();

void showAllStudPostInfo();

void showStudPostInfo(Student* student);

void showStudApplyPost(Post* post);

void readInfo(const char* path);

void writeInfo(const char* path);

int main()
{
	sysInit();
	readInfo("personne.dat");
	while (1)
	{
		system("cls");
		home();
		mainOption();
	}
	return 0;
}

void sysInit()
{
	//creer des listes chainees
	compHead = (Company*)calloc(1, sizeof(Company));
	studHead = (Student*)calloc(1, sizeof(Student));
}

void home()
{
	printf("***************************************************************\n");
	printf("BIENVENUE DANS LE SYSTEME DE GESTION DES STAGES!\n");
	printf("1. Gestion Des Comptes D'entreprise\n");
	printf("2. Gestion Des Comptes D'eleve\n");
	printf("0. Quitter Le Systeme\n\n");
	printf("****************************************************************\n");
}

void mainOption()
{
	printf("Entrez votre choix: ");
	int op = 0;
	scanf("%d", &op);
	switch (op)
	{
	case 0:
		writeInfo("personne.dat");
		system("pause");
		exit(0);
		break;
	case 1:
		compManage();
		break;
	case 2:
		studManage();
		break;
	default:
		printf("Erreurs de saisie, veuillez saisir a nouveau.\n");
		system("pause");
		getchar(); //fflush(stdin);
	}
}

void compManage()
{
	int ret;
	while (1)
	{
		system("cls");
		compMenu();
		ret = compOption();
		//retourner au menu principal
		if (ret == 0)
		{
			return;
		}
	}
}

void compMenu()
{
	printf("**********************************************\n\n");
	printf("SYSTEME DE GESTION D'ENTREPRISE\n");
	printf("1. Creer Un Compte D'entreprise\n");
	printf("2. Modifier Les Informations De Base De L'entreprise\n");
	printf("3. Modifier Les Informations De Stage En Entreprise\n");
	printf("4. Afficher Toutes Les Informations Sur Les Stages\n");
	printf("5. Supprimer Un Candidat\n");
	printf("0. Retour Au Menu Principal\n\n");
	printf("**********************************************\n");
}

int compOption()
{
	int op;
	printf("Entrez votre choix: ");
	scanf("%d", &op);
	switch (op)
	{
	case 0:
		break;
	case 1:
		registeComp();
		break;
	case 2:
		modifyCompBaseInfo();
		break;
	case 3:
		modifyCompPostInfo();
		break;
	case 4:
		showAllCompPostInfo();
		break;
	case 5:
		delPostStud();
		break;
	default:
		printf("Erreurs de saisie, veuillez saisir a nouveau.\n");
	}
	system("pause");
	getchar();
	return op;
}

void registeComp()
{
	//creer l'element de tete de la liste chainee de l'entreprise
	Company* compNode = (Company*)calloc(1, sizeof(Company));
    fflush(stdin);
	printf("Entrez le nom , l'adresse et le domaine de l'entreprise: ");
	scanf("%s%s%s", compNode->name, compNode->address, compNode->area);
	int n = 0;
	printf("Entrez le nombre de stages a creer: ");
	scanf("%d", &n);
	//creer l'element de tete de la liste chainee de stages propose par l'entreprise
	compNode->postHead = (Post*)calloc(1, sizeof(Post));
	while (n)
	{
		printf("Il reste %d de stage(s) a saisir\n", n);
		Post* postNode = (Post*)calloc(1, sizeof(Post));
		printf("entrez le nom de stage: ");
		scanf("%s", postNode->name);
		//ajouter les nouveaux stages a la liste chainee de stages proposes par l'entreprise
		postNode->next = compNode->postHead->next;
		compNode->postHead->next = postNode;
		n--;
	}
    //ajouter les prochaines entrepises dans la listes chainee de l'entreprise
	compNode->next = compHead->next;
	compHead->next = compNode;
}

void modifyCompBaseInfo()
{
	char compName[100] = { 0 };
	int flag = 0;//pour noter si l'entreprise a ete trouve
	printf("Entrez le nom de l'entreprise a modifier: ");
	scanf("%s", compName);
	//chercher l'entreprise
	Company* temp = compHead->next;//Position fixe du pointeur de tête
	while (temp)
	{
		if (strcmp(temp->name, compName)==0)
		{
			//modification
			printf("Entrez le nouveau nom, l'adresse et le domaine de l'entreprise: ");
			scanf("%s%s%s", temp->name, temp->address, temp->area);
			flag = 1;
			printf("Modifié avec succes\n");
			break;
		}
		temp = temp->next;
	}
	if (flag==0)
	{
		printf("L'entreprise n'a pas ete trouvee\n");
	}
}

void modifyCompPostInfo()
{
	char compName[100] = { 0 };
	char postName[100] = { 0 };
	char studName[50] = { 0 };
	int flag1 = 0;//noter pour l'entreprise
	int flag2 = 0;//noter pour le stage
	int flag3 = 0;

	printf("Entrez le nom de l'entreprise a modifier: ");
	scanf("%s", compName);
	Company* tempComp = compHead->next;
	Post* tempPost = NULL;
	Post* tempPostStud = NULL;
	Student* tempStud = studHead->next;
	Student* tempStudOther = studHead->next;
	while (tempComp)
	{
		if (strcmp(tempComp->name, compName)==0)
		{
			printf("Entrez le nom du stage a modifier: ");
			scanf("%s", postName);
			flag1 = 1;
			tempPost = tempComp->postHead->next;

			while (tempPost)
			{
				if (strcmp(tempPost->name, postName)==0)
				{
					flag2 = 1;
					printf("Entrer le nouveau nom: ");
					scanf("%s", tempPost->name);
					//afficher les candidatures
					showStudApplyPost(tempPost);
					//candidature acceptee
					printf("Entrez le nom du candidat que vous souhaitez admettre: ");
					scanf("%s", studName);
					tempStud = studHead->next;
					while (tempStud)
					{
						if (strcmp(tempStud->name, studName)==0)
						{
                            //l'eleve accepte
							tempPost->student = tempStud;
							//changer les statues
							tempPostStud = tempStud->postHead->next;
							while (tempPostStud)
							{
								if (strcmp(tempPostStud->name, postName)==0)
								{
									tempPostStud->status = 1;
									flag3 = 1;
									break;
								}
								tempPostStud = tempPostStud->next;
							}
						}
						if (flag3 == 1)
							break;
						else
							tempStud = tempStud->next;
					}
					while (tempStudOther)
					{
						if (tempStudOther != tempStud)
						{
							tempPost->student = tempStudOther;

							tempPostStud = tempStudOther->postHead->next;
							while (tempPostStud)
							{
								if (strcmp(tempPostStud->name, postName)==0)
								{
									tempPostStud->status = -1;
									break;
								}
								tempPostStud = tempPostStud->next;
							}
						}
						tempStudOther = tempStudOther->next;
					}
					break;
				}
				tempPost = tempPost->next;
			}
		}
		if (flag2 == 1)
			break;
		else
			tempComp = tempComp->next;
	}

	if (flag1==0 || flag2==0)
	{
		printf("Desole, ce stage n'existe pas.\n");
	}
}

void showAllCompPostInfo()
{
	Company* comp = compHead->next;
	while (comp)
	{
		showCompPostInfo(comp);
		comp = comp->next;
	}
}

void delPostStud()
{
	char compName[100] = { 0 };
	printf("Entrez le nom d'entreprise: ");
	scanf("%s", compName);
	char postName[100] = { 0 };

	Post* tempPost = NULL;
	Company* tempComp = compHead->next;
	Post* tempPostStud = NULL;
	Student* tempStud = NULL;
	int flag1 = 0, flag2 = 0, flag3 = 0;
	while (tempComp)
	{
		if (strcmp(compName, tempComp->name)==0)
		{
			printf("Entrez le nom du stage pour lequel le candidat doit etre supprime: ");
			scanf("%s", postName);
			flag1 = 1;
			tempPost = tempComp->postHead->next;
			while (tempPost)
			{
				if (strcmp(tempPost->name, postName)==0)
				{
					//changer le statue a -1
					tempPostStud = tempPost->student->postHead->next;
					while (tempPostStud)
					{
						if (strcmp(tempPostStud->name, tempPost->name)==0)
						{
							tempPostStud->status = -1;
							tempPost->student = NULL;
							flag3 = 1;
							break;
						}
						tempPostStud = tempPostStud->next;
					}

				}
				if (!flag3)
					tempPost = tempPost->next;
				else break;
			}
		}
		tempComp = tempComp->next;
	}
}

void showCompPostInfo(Company* comp)
{
    //afficher les entreprises
    printf("l'information de l'entreprise: \n %-20s\t%-20s\t%-20s\n", comp->name, comp->address, comp->area);
	printf("l'information de stage: \n");
	Post* post = comp->postHead->next;
	while (post)
	{
		//afficher les stages
		printf("%-5s\t", post->name );
		if (post->student == NULL)
			printf("%-5s\n", "Aucun candidat n'a encore ete accepte");
		else
			printf("%-5s\n", post->student->name);
		post = post->next;
	}
	printf("\n\n");
}

//pareil avec entreprise
void studManage()
{
	int ret = 0;
	while (1)
	{
		system("cls");
		studMenu();
		ret = studOption();
		if (ret == 0)
		break;
	}
}

void studMenu()
{
	printf("**********************************************\n\n");
	printf("Gestion Des Comptes De L'eleve\n");
	printf("1. Creer Un Compte D'eleve\n");
	printf("2. Modifier Les Informations De Base De L'eleve\n");
	printf("3. Supprimer Une Candidature\n");
	printf("4. Ajouter Une Candidature\n");
	printf("5. Afficher toutes les candidatures\n");
	printf("0. Retour Au Menu Principal\n\n");
    printf("**********************************************\n");
}

int studOption()
{
	int op;
	printf("Entrez votre choix: ");
	scanf("%d", &op);
	switch (op)
	{
	case 0:
		break;
	case 1:
		registeStud();
		break;
	case 2:
		modifyStudBaseInfo();
		break;
	case 3:
		delApplication();
		break;
	case 4:
		addApplication();
		break;
	case 5:
		showAllStudPostInfo();
		break;
	default:
		printf("Erreurs de saisie, veuillez saisir a nouveau.\n");
	}
	system("pause");
	getchar();
	return op;
}

void registeStud()
{
	Student* studNode = (Student*)calloc(1, sizeof(Student));
	printf("Entrez le nom d'eleve: ");
	scanf("%s", studNode->name);
	int n = 0;
	printf("Entrez le nombre de stage ou vous voulez postuler: ");
	scanf("%d", &n);
	studNode->postHead = (Post*)calloc(1, sizeof(Post));
	while (n)
	{
		printf("Il reste %d de stage(s) a saisir\n", n);
		Post* postNode = (Post*)calloc(1, sizeof(Post));
		if (!postNode)exit(-1);
		printf("Entrez le nom de stage: ");
		scanf("%s", postNode->name);
		postNode->next = studNode->postHead->next;
		studNode->postHead->next = postNode;
		n--;
	}
	studNode->next = studHead->next;
	studHead->next = studNode;
}

void modifyStudBaseInfo()
{
	printf("Entrez le nom de l'eleve a modifier: ");
	char studName[100] = { 0 };
	scanf("%s", studName);
	Student* temp = studHead->next;
	int flag = 0;
	while (temp)
	{
		if (strcmp(temp->name, studName)==0)
		{
			printf("Entrez le nouveau nom: ");
			scanf("%s", temp->name);
			flag = 1;
			break;
		}
		temp=temp->next;
	}
	if (flag==0)
	{
		printf("Desole, cet eleve n'existe pas\n");
	}
}

void delApplication()
{
	printf("Entrez le nom d'eleve a chercher: ");
	char studName[100] = { 0 };
	scanf("%s", studName);
	printf("entrez le stage a supprimer: ");
	char postName[100] = { 0 };
	scanf("%s", postName);
	Student* temp1 = studHead->next;
	int flag1 = 0, flag2 = 0;
	while (temp1)
	{

		if (strcmp(temp1->name, studName)==0)
		{
			Post* temp2 = temp1->postHead->next;
			while (temp2)
			{
				if (strcmp(temp2->name, postName)==0)
				{
					Post* prev = temp1->postHead;
					while (prev->next != temp2)
					{
						prev = prev->next;
					}
					prev->next = temp2->next;
					free(temp2);//supprimer cette candidature
					flag2 = 1;
					break;
				}
				temp2 = temp2->next;
			}
			flag1 = 1;
		}
		if (flag1==0)
			temp1 = temp1->next;
		else
			break;
	}
	if (flag1==0 || flag2==0)
	{
		printf("Desole, l'eleve ou le stage n'existe pas.\n");
	}
}

void addApplication()
{

	printf("Entrez le nom de l'eleve a chercher: ");
	char studName[100] = { 0 };
	scanf("%s", studName);
	Student* temp = studHead->next;
	int n = 0;
	int flag = 0;
	while (temp)
	{
		if (strcmp(temp->name, studName)==0)
		{
			printf("Entrez le nombre de stage a ajouter: ");
			scanf("%d", &n);
			while (n)
			{
				printf("Il reste %d stage(s) a ajouter\n", n);
				Post* postNode = (Post*)calloc(1, sizeof(Post));
				printf("Entrez le nom de stage: ");
				scanf("%s", postNode->name);
				postNode->next = temp->postHead->next;
				temp->postHead->next = postNode;
				n--;
			}
			flag = 1;
			break;
		}
		temp=temp->next;
	}
	if (flag==0)
	{
		printf("Desole, cet eleve n'existe pas.\n");
	}
}

void showAllStudPostInfo()
{
	Student* student = studHead->next;
	while (student)
	{
		showStudPostInfo(student);
		student = student->next;
	}
}

void showStudPostInfo(Student* student)
{
	Post* post = student->postHead->next;
	while (post)
	{
		printf("%-20s\t%-20s\t", student->name, post->name);
		if (post->status == 0)
			printf("%-20s\n", "Non decide");
		else if (post->status == -1)
			printf("%-20s\n", "Refuse");
		else
			printf("%-20s\n", "Accepte");

		post = post->next;
	}
	printf("\n\n");
}

void showStudApplyPost(Post* post)
{
	Student* stu = studHead->next;
	while (stu)
	{
		Post* temp = stu->postHead->next;
		while (temp)
		{
			if (strcmp(post->name, temp->name)==0)
			{
				printf("%-20s\t%-20s\t", stu->name, temp->name);
				if (temp->status == 0)
					printf("%-20s\n","Non decide");
				else if(temp->status==1)
					printf("%-20s\n", "Accepte");
				else
					printf("%-20s\n", "Refuse");
			}
			temp = temp->next;
		}
		stu = stu->next;
	}
}

void readInfo(const char* path)
{
	FILE* fp = fopen(path, "a");
	if (!fp)exit(-2);
	fclose(fp);
	fp = fopen(path, "r");
	fseek(fp, 0, SEEK_END);
	int nLen = ftell(fp);//longueur du fichier
	fseek(fp, 0, SEEK_SET);
    //fread les informations de l'entreprises
	while (nLen - ftell(fp) > 1)//comme fread toutes la fichier
	{
		Company* compTemp = (Company*)calloc(1, sizeof(Company));
		fscanf(fp, "%s %s %s\n", compTemp->name, compTemp->address, compTemp->area);
		compTemp->postHead = (Post*)calloc(1, sizeof(Post));

		//fread les informations de stages
		while (1)
		{
			Post* postTemp = (Post*)calloc(1, sizeof(Post));
			Student* studTemp = (Student*)calloc(1,sizeof(Student));
			fscanf(fp, "%s %s\n", postTemp->name, studTemp->name);
			//connecte les listes de stages
			postTemp->student = studTemp;
			postTemp->next = compTemp->postHead->next;
			compTemp->postHead->next = postTemp;

			//fread 3 characteres plus car chaque struct termine par '###'
			char buf[4] = { 0 };

			fread(buf, 1, 3, fp);
			if (strcmp(buf, "###")==0)
			{
				fseek(fp, 2, SEEK_CUR);
				break;
			}
			else
				fseek(fp, -3, SEEK_CUR);
		}
		//connecter la liste chainee d'entreprise
		compTemp->next = compHead->next;
		compHead->next = compTemp;
		char buf[4] = { 0 };

		fread(buf, 1, 3, fp);
		if (strcmp(buf, "---")==0)//on termine finalement avec '---'
			break;
		else
			fseek(fp, -3, SEEK_CUR);
	}
    // fread les infos des eleves
	while (nLen - ftell(fp) > 1)
	{
		Student* studTemp = (Student*)calloc(1, sizeof(Student));
		fscanf(fp, "%s\n", studTemp->name);
		studTemp->postHead = (Post*)calloc(1, sizeof(Post));
		while (1)
		{
			Post* postTemp = (Post*)calloc(1, sizeof(Post));
			fscanf(fp, "%s %d\n", postTemp->name, &(postTemp->status));

            postTemp->next = studTemp->postHead->next;
			studTemp->postHead->next = postTemp;

			char buf[4] = { 0 };
			fread(buf, 1, 3, fp);
			if (strcmp(buf, "###")==0)
			{
				fseek(fp, 2, SEEK_CUR);
				break;
			}
			else
				fseek(fp, -3, SEEK_CUR);
		}
		studTemp->next = studHead->next;
		studHead->next = studTemp;

		char buf[4] = { 0 };
		fread(buf, 1, 3, fp);
		if (strcmp(buf, "---")==0)
			break;
		else
			fseek(fp, -3, SEEK_CUR);
	}
	fclose(fp);
	//trier la relation entre les informations sur le stage
	Company* compTemp = compHead->next;
	while (compTemp)
	{
		Post* postTemp = compTemp->postHead->next;
		while (postTemp)
		{
			if (strcmp(postTemp->student->name, "(null)")==0)
			{
				free(postTemp->student);
				postTemp->student = NULL;
			}
			else
			{
				//rester juste les eleves qui sont accpetees
				Student* studTemp = studHead->next;
				while (studTemp)
				{
					if (strcmp(postTemp->student->name, studTemp->name)==0)
					{
						free(postTemp->student);
						postTemp->student = studTemp;

					}
					studTemp = studTemp->next;
				}
			}
			postTemp = postTemp->next;
		}
		compTemp = compTemp->next;
	}
}

void writeInfo(const char* path)
{
	FILE* fp = fopen(path, "w");
	//infos de l'entreprise
	Company* compTemp = compHead->next;
	while (compTemp)
	{
		fprintf(fp, "%s %s %s\n", compTemp->name, compTemp->address, compTemp->area);
		Post* postTemp = compTemp->postHead->next;
		while (postTemp)
		{
			fprintf(fp, "%s %s\n", postTemp->name, postTemp->student->name);


			postTemp = postTemp->next;
		}
		//on termine chaque entreprise par '###'
		fprintf(fp, "###\n");
		compTemp = compTemp->next;
	}
	//on termine chaque entreprise par '---'
	fprintf(fp, "---\n");

	//infos de l'eleve
	Student* studTemp = studHead->next;
	while (studTemp)
	{
		fprintf(fp, "%s\n", studTemp->name);
		Post* postTemp = studTemp->postHead->next;
		while (postTemp)
		{
			fprintf(fp, "%s %d\n", postTemp->name, postTemp->status);
			postTemp = postTemp->next;
		}
		studTemp = studTemp->next;
		fprintf(fp, "###\n");
	}
	fprintf(fp, "---\n");
	fclose(fp);
}
