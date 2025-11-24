#include <stdio.h>
#include <windows.h>

void CurrentTime() {
    SYSTEMTIME st;
    GetLocalTime(&st);

    printf("%04d-%02d-%02d %02d:%02d:%02d.%03d\n",
           st.wYear, st.wMonth, st.wDay,
           st.wHour, st.wMinute, st.wSecond,
           st.wMilliseconds);
}
void pressAnyKey() {
    printf("\nPress any key to continue (ESC: quit)... ");
    int ch = getch();
    if (ch == 27) { // ESC Ű
        printf("\nExiting program.\n");
        exit(0);
    }
    printf("\nContinuing...\n");
    Sleep(1000);system("cls");
}
int main(){
	unsigned int ip[4], mask[4];
	unsigned int ip_add = 0, mask_add = 0;
	int sub_cnt;
	
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	
	printf("\n============================================\n");
	printf("========== Network Adress System  ==========\n");
	printf("============================================\n");
	printf("Current Time: ");CurrentTime();
	
	printf("\nPress any key to start...");
    _getch();
	
	while(1){
		ip_add = 0; mask_add = 0;
		
		printf("\n>>> Enter IP Address: ");
		scanf("%u.%u.%u.%u", &ip[0],&ip[1],&ip[2],&ip[3]);
		
		printf(">>> Enter Subnet Mask: ");
		scanf("%u.%u.%u.%u", &mask[0],&mask[1],&mask[2],&mask[3]);
			
		printf(">>> Enter number of subnets: ");
		scanf("%d", &sub_cnt);
		
		for(int i=0; i<4; i++){
			ip_add = (ip_add << 8) | ip[i];
			mask_add = (mask_add << 8) | mask[i];
		}
		
		unsigned int net_add = ip_add & mask_add;
		unsigned int bro_add = net_add | (~mask_add);
		
		printf("\n======== Calculated Network Result ========\n");
		printf("Network Address: %u.%u.%u.%u\n",
		(net_add >> 24) & 0xFF,
		(net_add >> 16) & 0xFF,
		(net_add >> 8) & 0xFF,
		net_add & 0xFF);
		
		Beep(750,300);
		printf("Broadcast Address: %u.%u.%u.%u\n",
		(bro_add >> 24) & 0xFF,
		(bro_add >> 16) & 0xFF,
		(bro_add >> 8) & 0xFF,
		bro_add & 0xFF);
		
		Beep(750,300);
		int host = 0;
		unsigned int temp = ~mask_add;
		
		while(temp){
			if (temp & 1) host++;
			temp >>= 1; // temp = temp >> 1;
		}
		
		unsigned int host_count = (1U << host) - 2; //usable host count. 1U: unsign 1bit
		;printf("Usable Host Count: %u\n", host_count);
		Beep(750,300);
		
		if(sub_cnt == 0){
        	printf("\nFLSM subnetting skipped.\n");
        	Beep(750,300);
		}
		else{
			int prefix = 0;
	       	unsigned int temp_mask = mask_add;
	       	
	        while (temp_mask & 0x80000000) { //32bit
	            prefix++;
	            temp_mask <<= 1;
	        }
	        int add = 0;
	        while((1 << add) < sub_cnt) add++;
	        int n_prefix = prefix + add;
	        unsigned int new_mask = 0xFFFFFFFF << (32 - n_prefix);

	        unsigned int block_size = 1 << (32 - n_prefix);
	        unsigned int usable_hosts = block_size - 2;
	        
	        printf("\n=== FLSM Subnetting Result ===\n");
        	printf("Old Mask: /%d\n", prefix);
        	printf("New Mask: /%d\n", n_prefix);
        	printf("Usable Hosts per Subnet: %u\n", usable_hosts);
        	
        	for (int i = 0; i < sub_cnt; i++) {
            unsigned int subnet_net = (ip_add & mask_add) + (i * block_size);
            unsigned int subnet_bro = subnet_net + block_size - 1;

            printf("\nSubnet ");printf("%d", i + 1);printf(":\n");
            printf("  Network: %u.%u.%u.%u\n",
                   (subnet_net >> 24) & 0xFF,
                   (subnet_net >> 16) & 0xFF,
                   (subnet_net >> 8) & 0xFF,
                   subnet_net & 0xFF);
            printf("  Broadcast: %u.%u.%u.%u\n",
                   (subnet_bro >> 24) & 0xFF,
                   (subnet_bro >> 16) & 0xFF,
                   (subnet_bro >> 8) & 0xFF,
                   subnet_bro & 0xFF);
                   
            int r = 200 + rand() % 500;
            Beep(r,300);
			}
		}
		pressAnyKey();
	}
	return 0;
}
