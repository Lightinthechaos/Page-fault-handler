/*
 * PageFaultHandlers.c
 *
 *  Created on: 2018 M12 5
 *      Author: liux8275
 */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main(void){
	//setbuf(stdout, NULL);
	char* token1;
	char* token2;
	char str[100];
	int count = 0;
	int i=0;
	int p=0;
	int process_number[50][2];// 50 maybe can be changed
	int num_frame;
	int process[100];// 100 maybe can be changed
	int vp[100];// 100 maybe can be changed
	int index = 0;
	int flag = 1;
	int check = 1;
	fgets(str, 10, stdin);
	str[strlen(str)-1] = '\0';

	//set all pagefault of indicate process = 0;
	for (int j=0;j<50;j++){
		process_number[j][0] = 0;
		process_number[j][1] = 0;
	}

	if (strcmp(str, "GLOBAL") == 0){

		fgets(str, 10, stdin);
		num_frame = atoi(str);
		//printf("number of frame: %d\n",num_frame);
		int global_array[num_frame][2];
		for (int j=0;j<num_frame;j++){
			global_array[j][0] = 0;
			global_array[j][1] = 0;
		}
		fgets(str, 10, stdin);

		while (strcmp(str, "\n") != 0){
			check = 1;
			flag = 1;
			//printf("hello");
			token1 = strtok(str, " ");
			token2 = strtok(NULL," ");
			//printf("process: %d vp:%d\n",atoi(token1),atoi(token2));
			process[i] = atoi(token1);
			vp[i] = atoi(token2);
			if (count == num_frame){
				count = 0;
			}
			//printf("count: %d\n",count);
			// check if new input is already exsit in porcess;
			for (int j=0;j<50;j++){
				if (atoi(token1) == process_number[j][0]){
					check = 0;
				}
			}
			if (check == 1){
				process_number[index][0] = atoi(token1);
				index ++; // index means how many process have;
			}
			//printf("inside index:%d\n",index);
			// check if new input exists in frame
			for (int j=0;j<num_frame;j++){
				if (atoi(token1) == global_array[j][0] && atoi(token2) == global_array[j][1]){
					flag = 0;
				}
			}
			// if not in frame then add it in;
			if (flag == 1){

				global_array[count][0] = atoi(token1);
				global_array[count][1] = atoi(token2);

				//printf("global_array: %d %d count:%d\n",global_array[count][0],global_array[count][1],count);
				count ++;
				for (int j=0;j<50;j++){
					if (process_number[j][0] == atoi(token1)){
						process_number[j][1] = process_number[j][1] + 1;
					}
				}
			}
			i++;

			fgets(str, 10, stdin);
		}
		//printf("page frame:\n");
		//printf("global array:\n");
		//for (int a=0;a<num_frame;a++){
		//	printf("%d %d\n",global_array[a][0],global_array[a][1]);
		//}
		//printf("index: %d", index);
		//printf("number of frame:%d", num_frame);
		//printf("Expected Output\n");
		printf("PID Page Faults\n");
		for (int j=0;j<index;j++){
			printf("%d    %d\n",process_number[j][0], process_number[j][1]);
		}
		for (int j=0;j<index;j++){
			printf("Process %d page table\n",process_number[j][0]);
			printf("Page Frame\n");
			for (int k=0;k<num_frame;k++){
				if (process_number[j][0] == global_array[k][0]){
					//printf("process ID: %d  global array: %d  j: %d k: %d\n", process_number[j][0],global_array[k][0],j,k);
					printf("%d    %d\n", global_array[k][1],k);
				}
			}
		}
	}

	if (strcmp(str, "LOCAL") == 0){
		fgets(str, 10, stdin);
		num_frame = atoi(str);
		fgets(str, 10, stdin);

		while (strcmp(str, "\n") != 0){
			check = 1;
			token1 = strtok(str, " ");
			token2 = strtok(NULL," ");

			process[i] = atoi(token1);
			vp[i] = atoi(token2);

			// check if new input is already exsit in porcess;

			for (int j=0;j<50;j++){
				if (atoi(token1) == process_number[j][0]){
					check = 0;
				}
			}
			if (check == 1){
				process_number[index][0] = atoi(token1);
				index ++; // index means how many process have;
			}
			i++;
			fgets(str, 10, stdin);
		}
		int local_array[index*num_frame][2];
		for (int g=0;g<index*num_frame;g++){
			local_array[g][0]=0;
			local_array[g][1]=0;
		}
		//printf("index*num_frame: %d\n", index*num_frame);
		while (p<index*num_frame){
			flag = 1;
			for (int j=0;j<index*num_frame;j++){
				if (process[p] == local_array[j][0] && vp[p] == local_array[j][1]){
					flag = 0;
				}
			}
			if (flag == 1){
				//process_number[p][0] = local_array[p][0];
				local_array[p][0] = process[p];
				local_array[p][1] = vp[p];
				//printf("local array: %d  %d\n",local_array[p][0],local_array[p][1]);
			}
			for (int j=0;j<50;j++){
				if (process_number[j][0] == process[p]){
					process_number[j][1] = process_number[j][1] + 1;
				}
			}
			p++;
		}
		int t = 0;
		for (int v=0;v<index;v++){
			for (int j=0;j<index*num_frame;j++){
				if (process_number[v][0] == process[j]){
					local_array[t][0] = process[j];
					local_array[t][1] = vp[j];
					t++;
					//printf("local array: %d  %d\n",local_array[j][0],local_array[j][1]);
				}
			}
		}

		//printf("number of frame:%d\n", num_frame);
		//printf("Expected Output\n");
		printf("PID Page Faults\n");
		for (int j=0;j<index;j++){
			printf("%d    %d\n",process_number[j][0], process_number[j][1]);
		}
		for (int j=0;j<index;j++){
			printf("Process %d page table\n",process_number[j][0]);
			printf("Page Frame\n");
			for (int k=0;k<index*num_frame;k++){
				if (process_number[j][0] == local_array[k][0]){
					printf("%d    %d\n", local_array[k][1],k);
				}
			}
		}
	}


}
