#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"MyLibrary.h"

typedef enum
{
	ADD		= 0x01,
	FIND	= 0x02,
	PRINT	= 0x04,
	DELETE	= 0x08,
	QUIT	= 0x10
}work;

typedef union
{
	size_t size;
	char character[sizeof(size_t)];
}size_char;

work chose_a_work(void);
int find_the_name_from_arguments(FILE **file, char *name);
int find_a_name(void);
void add_the_name_from_arguments(FILE **file, char *name);
int add_a_name(void);
int delete_the_name_from_arguments(char *file_name, char *the_name_to_be_deleted);
int delete_a_name(void);
void get_names_in_a_file_from_arguments(FILE **file);
int get_names_in_a_file(void);

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		switch ((strcmp(argv[1], "q") == 0) * QUIT | (strcmp(argv[1], "d") == 0) * DELETE | (strcmp(argv[1], "p") == 0) * PRINT | (strcmp(argv[1], "f") == 0) * FIND | (strcmp(argv[1], "a") == 0) * ADD)
		{
			FILE *file_pointer;
		case ADD:
			if (argc == 4)
			{
				if (fopen_s(&file_pointer, argv[2], "a+") != 0)
				{
					printerr("Failure to open the file!\n");
					break;
				}
				if (file_size(file_pointer) == 0 || find_the_name_from_arguments(&file_pointer, argv[3]) != 1) add_the_name_from_arguments(&file_pointer, argv[3]);
				fclose(file_pointer);
			}
			break;
		case FIND:
			if (argc == 4)
			{
				if (fopen_s(&file_pointer, argv[2], "r") != 0)
				{
					printerr("Failure to open the file!\n");
					break;
				}
				switch (find_the_name_from_arguments(&file_pointer, argv[3]))
				{
				case 1:
					printerr("There is his or her name in the file.\n");
					break;
				case 0:
					printerr("There isn'n his or her name in the file.\n");
					break;
				}
				fclose(file_pointer);
			}
			break;
		case PRINT:
		{
			if (argc == 3)
			{
				if (fopen_s(&file_pointer, argv[2], "r") != 0)
				{
					printerr("Failure to open the file!\n");
					break;
				}
				get_names_in_a_file_from_arguments(&file_pointer);
				fclose(file_pointer);
			}
			break;
		}
		case DELETE:
		{
			if (argc == 4)
			{
				delete_the_name_from_arguments(argv[2], argv[3]);
			}
		break;
		}
		case QUIT:
			return EXIT_SUCCESS;
			break;
		}
	}
	while (TRUE)
	{
		switch (chose_a_work())
		{
		case ADD:
			switch (add_a_name())
			{
			case EXIT_SUCCESS:
				printerr("Success!\n");
				break;
			case EXIT_FAILURE:
				printerr("Failure to open the file!\n");
				break;
			}
			break;
		case FIND:
			switch (find_a_name())
			{
			case 1:
				printerr("There is the name in the file.\n");
				break;
			case 0:
				printerr("There is not the name in the file.\n");
				break;
			case -1:
				printerr("Failure to open the file!\n");
				break;
			}
			break;
		case PRINT:
		{
			switch (get_names_in_a_file())
			{
			case EXIT_SUCCESS:
				printerr("Success!\n");
				break;
			case EXIT_FAILURE:
				printerr("Failure to open the file!\n");
				break;
			}
			break;
		}
		case DELETE:
		{
			switch (delete_a_name())
			{
			case 1:
				printerr("Deleted!\n");
				break;
			case 0:
				printerr("There is not the name in the file.\n");
				break;
			case -1:
				printerr("Failure to open the file!\n");
				break;
			}
			break;
		}
		case QUIT:
			return EXIT_SUCCESS;
			break;
		}
	}
}

work chose_a_work(void)
{
	char *entered;
	while (TRUE)
	{
		printerr("(a)Add a name to a file.\n");
		printerr("(f)Find a name in a file.\n");
		printerr("(p)Print names in a file.\n");
		printerr("(d)Delete a name in a file.\n");
		printerr("(q)Quit the program.\n");
		printerr("Enter a character. -->");
		entered = input();
		if (strcmp(entered, "a") == 0)
		{
			free(entered);
			return ADD;
		}
		if (strcmp(entered, "f") == 0)
		{
			free(entered);
			return FIND;
		}
		if (strcmp(entered, "p") == 0)
		{
			free(entered);
			return PRINT;
		}
		if(strcmp(entered, "d") == 0)
		{
			free(entered);
			return DELETE;
		}
		if (strcmp(entered, "q") == 0)
		{
			free(entered);
			return QUIT;
		}
		free(entered);
		printerr("Enter ""a"", ""f"", ""p"" or ""q""\n");
	}
}

int find_the_name_from_arguments(FILE **file, char *name)
{
	char *got_name;
	size_t i;
	size_char size_of_got_name;
	int continue_or_not = TRUE;
	fseek(*file, 0L, SEEK_SET);
	while (continue_or_not)
	{
		for (i = 0; i < sizeof(size_char); i++)fscanf_s(*file, "%c", size_of_got_name.character + i, 1);
		if (ftell(*file) + size_of_got_name.size == file_size(*file))continue_or_not = FALSE;
		got_name = (char*)calloc_s(size_of_got_name.size + 1, sizeof(char));
		for (i = 0; i < size_of_got_name.size; i++)fscanf_s(*file, "%c", got_name + i, 1);
		if (strcmp(name, got_name) == 0)
		{
			free(got_name);
			return 1;
		}
		free(got_name);
	}
	return 0;
}

int find_a_name(void)
{
	char *file_name, *entered_name;
	int returned;
	FILE* file_pointer;
	printerr("Enter the name of file. -->");
	file_name = input();
	fopen_s(&file_pointer, file_name, "r");
	free(file_name);
	if (file_pointer == NULL)return -1;
	printerr("Enter name. -->");
	entered_name = input();
	returned = find_the_name_from_arguments(&file_pointer, entered_name);
	free(entered_name);
	fclose(file_pointer);
	return returned;
}

void add_the_name_from_arguments(FILE **file, char *name)
{
	size_t i;
	size_char size_of_writen_name;
	fseek(*file, 0L, SEEK_END);
	size_of_writen_name.size = 0;
	while (name[size_of_writen_name.size] != '\0')size_of_writen_name.size++;
	for (i = 0; i < sizeof(size_char); i++)fprintf(*file, "%c", size_of_writen_name.character[i]);
	fprintf(*file, "%s", name);
	return;
}

int add_a_name(void)
{
	char *file_name, *name;
	FILE *file_pointer;
	printerr("Enter the name of file. -->");
	file_name = input();
	fopen_s(&file_pointer, file_name, "a+");
	free(file_name);
	if (file_pointer == NULL)return EXIT_FAILURE;
	printerr("Enter name. -->");
	name = input();
	if (file_size(file_pointer) == 0 || find_the_name_from_arguments(&file_pointer, name) != 1)add_the_name_from_arguments(&file_pointer, name);
	free(name);
	fclose(file_pointer);
	return EXIT_SUCCESS;
}

void get_names_in_a_file_from_arguments(FILE **file)
{
	char **names = calloc_s(1, sizeof(char*)), **new_names;
	size_t number_of_names = 0, i;
	size_char got_name_size;
	int continue_or_not = TRUE;
	if (file_size(*file) == 0)return;
	fseek(*file, 0L, SEEK_SET);
	while (continue_or_not)
	{
		new_names = calloc_s(++number_of_names, sizeof(char*));
		for (i = 0; i < number_of_names - 1; i++)new_names[i] = names[i];
		for (i = 0; i < sizeof(size_char); i++)fscanf_s(*file, "%c", got_name_size.character + i, 1);
		new_names[number_of_names - 1] = (char*)calloc_s(got_name_size.size + 1, sizeof(char));
		for (i = 0; i < got_name_size.size; i++)fscanf_s(*file, "%c", new_names[number_of_names - 1] + i, 1);
		if (ftell(*file) == file_size(*file))continue_or_not = FALSE;
		free(names);
		names = new_names;
	}
	for (unsigned int i = 0; i < number_of_names; i++)printf("%s\n", names[i]);
	for (i = 0; i < number_of_names; i++)free(names[i]);
	free(names);
	return;
}

int get_names_in_a_file()
{
	char *file_name;
	FILE *file_pointer;
	printerr("Enter the name of file. -->");
	file_name = input();
	fopen_s(&file_pointer, file_name, "r");
	free(file_name);
	if (file_pointer == NULL)return EXIT_FAILURE;
	get_names_in_a_file_from_arguments(&file_pointer);
	fclose(file_pointer);
	return EXIT_SUCCESS;
}

int delete_the_name_from_arguments(char *file_name, char *the_name_to_be_deleted)
{
	int deleted_or_not = FALSE;
	FILE *file_pointer;
	char *file_content,*a_name_in_the_file;
	size_t i, size_of_the_file, file_cursor = 0;
	size_char name_size;
	fopen_s(&file_pointer, file_name, "r");
	if (file_pointer == NULL)return -1;
	fseek(file_pointer, 0L, SEEK_SET);
	size_of_the_file = file_size(file_pointer);
	file_content = calloc_s(size_of_the_file + 1, sizeof(char));
	for (i = 0; i < size_of_the_file; i++)fscanf_s(file_pointer, "%c", file_content+i, 1);
	fclose(file_pointer);
	fopen_s(&file_pointer, file_name, "w");
	if (file_pointer == NULL)return -1;
	while(file_cursor < size_of_the_file)
	{
		for (i = 0; i < sizeof(size_char); i++)name_size.character[i] = file_content[file_cursor + i];
		file_cursor += sizeof(size_char);
		a_name_in_the_file=calloc_s(name_size.size+1, sizeof(char));
		for (i = 0; i < name_size.size; i++)a_name_in_the_file[i] = file_content[file_cursor + i];
		file_cursor += name_size.size;
		if (strcmp(a_name_in_the_file, the_name_to_be_deleted) != 0)
		{
			for (i = 0; i < sizeof(size_char); i++)fprintf_s(file_pointer, "%c", name_size.character[i]);
			for (i = 0; i < name_size.size; i++)fprintf_s(file_pointer, "%c", file_content[file_cursor - name_size.size + i]);
		}
		else deleted_or_not = TRUE;
		free(a_name_in_the_file);
	}
	fclose(file_pointer);
	free(file_content);
	return deleted_or_not;
}

int delete_a_name(void)
{
	int returned;
	char *file_name, *the_name_to_be_deleted;
	printerr("Enter the name of file. -->");
	file_name = input();
	printerr("Enter the name to be deleted. -->");
	the_name_to_be_deleted = input();
	returned = delete_the_name_from_arguments(file_name, the_name_to_be_deleted);
	free(file_name);
	free(the_name_to_be_deleted);
	return returned;
}
