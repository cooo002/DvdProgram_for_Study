//
//  main.c
//  DVDPro
// x code에서 실행하면 어쩔 수 없이 한글이 분리되어서 출력된다. 그 이유는 인코딩 방식에서 발생되는 문제
//때문인거 같다!!!
//  Created by 김재석 on 17/12/2018.
//  Copyright © 2018 김재석. All rights reserved.
//다시 시작할 때 체크할 것
// 1. 왜 삭제관련된 부분이 안되는지
// 2. 과연 리스트가 잘 연결 되었는가??( 출력 함수를 작성해서 한번 확인해보자 =)
// 3. 분명 fflush 사용했는데 왜 버퍼에 엔터가 남아 있어서 이름 입력 란을 그냥 넘어가는지?? 알아보자!
// 4. 정보 추가하는 함수에 배열 선언하고 그 안에 이름 입력하고 저장함(check)
// 5. 한글 분리되어 출력되는 현상 x code의 문제점인거 확인 ( 이 부분 무시하고 다음 함수 구현하자 !!)
// 6. 대여 정보 입력하는 함수부터 다시 하기( 그냥 정수로 해서 +7해서 반납일 정할 수 도 있지만 다른 방법 생각해
// 7. 대여 정보에 관련된 내용중  대여정보 입력, 반납까지 함수로 구현함 다시 시작할 때 그 부분 체크하기!!
//.    보자!!!)
// 8. 특정회원 이름으로 대여정보를 검색하는 기능 완성( 이걸 기반으로 다른 serch기능을 담당하는 함수 구현하자)
// 9. 연체, 블랙 리스트 만들기
//.   es) 해당 이름의 회원 정보 출력, 해당 dvd에 정보를 출려
//dvd 프로그램
// check just fof github

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_CHAR 30;

//    = 고객 정보 :  이름, 전화번호 , 
typedef struct PersnoInfoNode{
    int Phone;
    int delayNumberOfTime; // 나중에 연체 리스트, 블랙 리스트를 판단하는 지표로 사용
    char* name;
    // 앞으로 구조체에서 문자열을 입력 받을 때는 이렇게 포인터 타입으로 쓰자 !!!
    struct PersnoInfoNode *nextNode;
}PersoonInfoNode;

int size = 0; // 기본 가입 정보에서 리스트가 제대로 입력되었나 확인하기 위해 for문 돌릴 때 사용
int dvdSize = 0; // dvd와 관련된 함수에서 for문 돌리기 위해 사용
int RentalSize = 0; // 대야 정보와 관련되 함수에서 for문을 돌리기 위해 사용
// dvd 정보 : isbn , 제목, 장르, 출시년도

typedef struct dvdInfoNode{
    char *isbn;
    char *dvdName;
    char *genre;
    int madeYear;
    struct dvdInfoNode *nextNode;
}dvdInfoNode;

// 대여 정보  dvd 제목, 대여자 , 대여 날짜 \, 반납 날짜, 연체 연부
typedef struct RentalInfoNode{
    char *RdvdName; // dvd 이름
    char *RpersonName;// 대여자 이름
    int Rdate[3]; // 빌린 날짜
    int ReturnDate[3]; // 반납 날짜
    char *overDue; // 대여 상태
    struct RentalInfoNode *nextNode;
}RentalInfoNode;


PersoonInfoNode *firstPersonNode=NULL;//첫번째 노드 ( 고객정보 추가와 관련된 첫번째 노드)
PersoonInfoNode *lastPersnonNode=NULL;//마지막 노드

dvdInfoNode *firstDvdInfoNode = NULL; // dvd추가 관련  첫번째 노드
dvdInfoNode *lastDvdInfoNode = NULL;

RentalInfoNode *firstRentalInfoNode = NULL;
RentalInfoNode *lastRentalInfoNode = NULL;

/////////////////////////////////////////////////////////
//고객관리
void Personinfo(){
    int phoneNum = 0;
    char* infoname = malloc(sizeof(char)*30); // 입력 받은 문자열이 계속 한 곳에
    // 덮어 씌어지게 되어서  나중에 출력할 때 똑같은 이름이 입력되는 것
    PersoonInfoNode *newnode = (PersoonInfoNode *)malloc(sizeof(PersoonInfoNode));
    printf("이름을 입력해주세요\n");
    scanf("%s", infoname); // 문자열을 입력 받을때는 & 연산자는 필요없다.
    fflush(stdin);
    printf("핸드폰 번호를 '-'제외하고 입력해주세요 \n");
    scanf("%d", &phoneNum);
    fflush(stdin);
    newnode -> Phone = phoneNum;
    newnode -> name = infoname;
    newnode -> delayNumberOfTime = 0;
    newnode -> nextNode = NULL;
    if(firstPersonNode == NULL){
        firstPersonNode = newnode;
        lastPersnonNode = newnode;
        size = size+1;
    }
    else{
        lastPersnonNode -> nextNode = newnode;
        lastPersnonNode = newnode;
        size = size+1;
    }
    printf("신규 회원 등록이 완료되었습니다.");
    
    return;
    
}

void PersoninfoDelete(){
    char* infoname = malloc(sizeof(char)*30); // 검색하고 싶은 이름이 저장되는 문자열 변수
    PersoonInfoNode *temp = firstPersonNode; // temp에 firstNode넣어줘야
    printf("이름을 입력해주세요\n");
    scanf("%s", infoname);
    fflush(stdin);
    if(firstPersonNode == NULL){// 하는거 아니야?? (내가 바꿔줘어써1
        
        printf("입력된 손님 정보가 없어 삭제 할 것도 없습니다. \n");
        return;
    }
    ////////////////////////////
    if(!strcmp(firstPersonNode->name,infoname)){// 첫번째 노드의 이름과 입력한 이름이 같을 경우
        firstPersonNode = firstPersonNode->nextNode;
        free(temp);
        size = size-1;
        printf("검색하신 손님의 정보를 삭제 하였습니다.");
    }
    else{
        PersoonInfoNode* before = firstPersonNode;
        while(1){
            if(!strcmp(temp->nextNode->name,infoname)){ // 두번째 노드 이 후부터 검색한 이름이 있는 경우(temp가 가르키는 다음 노드에 이름와 비교 )
                PersoonInfoNode *node_free = temp->nextNode; // (비교대상이 temp에 다음)
                before -> nextNode = temp -> nextNode-> nextNode;// 노드이니까 삭제도 다음 노드가 삭제되어)
                free(node_free);//
                size = size-1;
                printf("검색하신 손님의 정보를 삭제 하였습니다.");
                break;
            }
            else{
                if(temp->nextNode == NULL){ // 다음에 손님정보에 대해 내가 입력한 값이라
                    printf("더이상 저장된 손님 정보가 없습니다. \n");// 비교하고 싶어도 더 이상
                    break;// 저장된 손님 정보가 없는 경우
                }
                before = before->nextNode;// 현재 손님 정보와 입력한 이름이 일치하지 않아서
                temp = temp->nextNode;// 다음에 손님정보에서 검색하기위해 변수들의 값을 바꾸는 것이다.
            }
        }
    }
    return;
}
void personInfoCheck(){ //  리스트 연결 되었나 확인하기 위한 함수
    int i = 0; // for문을 돌리기 위해 사용하는 변수
    PersoonInfoNode *temp = malloc(sizeof(PersoonInfoNode));
    temp = firstPersonNode;
    printf(" \n현재 저장된 손님의 정보는 아래와 같습니다. \n");
    if( firstPersonNode == NULL){
        printf("\n저장된 손님 정보가 없어서 정보를 출력 할 수 없습니다. \n");
        return;
    }
    else{
        for(i ;  i < size ; i ++){
            printf("\n<-------------------->\n");
            printf("\n 이름 : %s\n" , temp->name);
            printf("\n 번호 : %d\n", temp->Phone);
            printf("\n 연체 횟수 : %d회\n", temp->delayNumberOfTime);
            printf("\n<-------------------->\n");
            temp = temp->nextNode;
        }
    }
}

/////////////////////////dvd 추가 관련된 기능을 가진 함수들 ///////////////////////////////
// dvd 정보 입력, 삭제
void dvdInfo(){
    int dvdmadeYear = 0;
    char* dvdname = malloc(sizeof(char)*30);
    char* dvdgenre = malloc(sizeof(char)*30);// 입력 받은 문자열이 계속 한 곳에
    char* dvdisbn = malloc(sizeof(char)*10) ;// 덮어 씌어지게 되어서  나중에 출력할 때 똑같은
    dvdInfoNode *newnode = (dvdInfoNode *)malloc(sizeof(dvdInfoNode));
    printf("dvd 제목을 입력해주세요\n");
    scanf("%s", dvdname); // 문자열을 입력 받을때는 & 연산자는 필요없다.
    fflush(stdin);
    printf("isbn의 앞 부분은 제외하고 뒤에'3'자리만 입력해주세요 \n");
    scanf("%s", dvdisbn);
    fflush(stdin);
    printf("dvd의 장르를 입력해주세요 \n");
    scanf("%s", dvdgenre);
    fflush(stdin);
    printf("발매년도를 입력해주세요 \n");
    scanf("%d", &dvdmadeYear);
    fflush(stdin);
    newnode -> dvdName = dvdname;
    newnode -> genre = dvdgenre;
    newnode -> isbn = dvdisbn;
    newnode -> madeYear = dvdmadeYear;
    newnode -> nextNode = NULL;
    
    if(firstDvdInfoNode == NULL){
        firstDvdInfoNode = newnode;
        lastDvdInfoNode = newnode;
        dvdSize = dvdSize+1;
    }
    else{
        lastDvdInfoNode -> nextNode = newnode;
        lastDvdInfoNode = newnode;
        dvdSize = dvdSize+1;
    }
    printf("신규 회원 등록이 완료되었습니다.");
    
    return;
    
}

void dvdInfoDelete(){
    char* dvdname = malloc(sizeof(char)*30); // 검색하고 싶은 이름이 저장되는 문자열 변수
    dvdInfoNode *temp = firstDvdInfoNode; // temp에 firstdvdNode넣어준거
    printf("dvd 제목을 입력해주세요\n");
    scanf("%s", dvdname);
    fflush(stdin);
    if(firstDvdInfoNode == NULL){// 하는거 아니야?? (내가 바꿔줘어써1
        
        printf("매장에 입력된 dvd 정보가 없어 삭제 할 것도 없습니다. \n");
        return;
    }
    ////////////////////////////
    if(!strcmp(firstDvdInfoNode->dvdName,dvdname)){// 첫번째 노드의 이름과 입력한 이름이 같을 경우
        firstDvdInfoNode = firstDvdInfoNode->nextNode;
        free(temp);
        dvdSize = dvdSize-1;
        printf("검색하신 dvd의 정보를 삭제 하였습니다.");
    }
    else{ // 첫번째에 검색한 정보와 일치하는 정보가 없을 경우
        dvdInfoNode* before = firstDvdInfoNode;
        while(1){
            if(!strcmp(temp->nextNode->dvdName,dvdname)){ // 두번째 노드 이 후부터 검색한 이름이 있는 경우(temp가 가르키는 다음 노드에 이름와 비교 )
                // 문장열이 서로 같은 경우 strcmp()함수는 0을 반환한다.
                dvdInfoNode *node_free = temp->nextNode; // (비교대상이 temp 다음
                before -> nextNode = temp -> nextNode-> nextNode;// 노드이니까 삭제도 다음 노드가 삭제되어)
                free(node_free);//
                dvdSize = dvdSize-1;
                printf("검색하신 dvd의 정보를 삭제 하였습니다.");
                break;
            }
            else{
                if(temp->nextNode == NULL){ // 다음에 손님정보에 대해 내가 입력한 값이라
                    printf("더이상 저장된 손님 정보가 없습니다. \n");// 비교하고 싶어도 더 이상
                    break;// 저장된 손님 정보가 없는 경우
                }
                before = before->nextNode;// 현재 손님 정보와 입력한 이름이 일치하지 않아서
                temp = temp->nextNode;// 다음에 손님정보에서 검색하기위해 변수들의 값을 바꾸는 것이다.
            }
        }
    }
    return;
}
// 저장된 dvd의 정보를 보기 위해 사용하는 함수
void dvdInfoCheck(){
    int i = 0; // for문을 돌리기 위해 사용하는 변수
    dvdInfoNode *temp = malloc(sizeof(dvdInfoNode));
    temp = firstDvdInfoNode;
    printf(" \n현재 보유하고 있는 dvd의 정보는 아래와 같습니다. \n");
    if( firstDvdInfoNode == NULL){
        printf("\n현재 보유하고 있는 dvd가 없어서 정보를 출력 할 수 없습니다. \n");
        return;
    }
    else{
        for(i ;  i < dvdSize ; i ++){
            printf("\n<-------------------->\n");
            printf("\n dvd 제목: %s\n" , temp->dvdName);
            printf("\n dvd 장르 : %s\n", temp->genre);
            printf("\n dvd 발매년도 : %d\n" , temp->madeYear);
            printf("\n dvd isbn 마지막 3자리 : %s\n" , temp->isbn);
            printf("\n<-------------------->\n");
            temp = temp->nextNode;
        }
    }
}
///////////////// 대여 정보 관련된 내용 출력 //////////////////////////////////
// dvd 대여 정보 ( dvd 이름으로 대영여부 확인 )
void RentalDvdInfo(){
    int RentalOrReturn = 0; // 여기저장된 수를 통해 반납, 대여, 연체 기능을 수행 할 수 있다.
    ///////// 대여 상태 구조체에 속하는 정돈 /////////
    char* rdvdname = malloc(sizeof(char)*30); // 입력
    char* rPersonName = malloc(sizeof(char)*30);// 입력
    char* rStatus = malloc(sizeof(char)*10) ;// 대여 상태
    
    time_t t = time(NULL); // 현재 날짜 출력을 위한 것
    struct tm tm = *localtime(&t);// 현재 날짜 출력을 위한 것
    
    
    /////////////////////////////////////////
    RentalInfoNode *newnode = (RentalInfoNode *)malloc(sizeof(RentalInfoNode));
    printf("\n1: 대여 \n ");
    printf("\n2: 반납 \n ");
    scanf("%d", &RentalOrReturn);
    fflush(stdin);
    if(RentalOrReturn == 1){ // dvd 이름, 대여자 이름 이렇게 2개만 입력할꺼다(나머지는 자동으로 입력되도록 )
        printf("빌린 사람의 이름을 입력해주세요 \n");
        scanf("%s", rPersonName); // 문자열을 입력 받을때는 & 연산자는 필요없다.
        fflush(stdin);
        printf("빌리고자하는 dvd 제목을 입력해주세요 \n");
        scanf("%s", rdvdname);
        fflush(stdin);
        newnode -> RdvdName = rdvdname;
        newnode -> RpersonName = rPersonName;
        ///////나머지는 자동으로 입력되도록
        /////////  빌린 날짜가 구조체에 저장되는 것 //////////
        newnode -> Rdate[0] = tm.tm_year+1900;
        newnode -> Rdate[1] = tm.tm_mon+1;
        newnode -> Rdate[2] = tm.tm_mday;
        //////// 반납 날짜가 구조체에 저장되는 것/////////
        // 반납 날짜는 25일 기준은 나눌꺼야 이유는 31일 이상이 되면  달이 넘어가니가/////
        if( newnode->Rdate[2] <= 24){ //현재 날짜가 24일 이하인 경우
            newnode->ReturnDate[0] = tm.tm_year+1900;
            newnode->ReturnDate[1] = tm.tm_mon+1;
            newnode->ReturnDate[2] = tm.tm_mday+7;
            
        }else{ // 일수기 24일 이상일 경우
            if(newnode -> Rdate[1] == 12){ // 12월에서 달이 넘어가게 되면 1월로 돌아가기 때문에
                newnode->ReturnDate[0] = tm.tm_year+1901; // 원래는 그냥 1900하면 현재 년도 뜨는데 12월에서
                newnode->ReturnDate[1] = tm.tm_mon-10; // 1월로 리세 해줌
                newnode->ReturnDate[2] = tm.tm_mday-24; // 1일로 리셋 해줌
            }
            else{
                newnode->ReturnDate[0] = tm.tm_year+1900;
                newnode->ReturnDate[1] = tm.tm_mon-11; // 1월로 리세 해줌
                newnode->ReturnDate[2] = tm.tm_mday-24; // 1일로 리셋 해줌
            }
            
        }
        ///////// 반납 날짜가 구조체에 저장되느 것 ////
        newnode -> overDue = "RENTAL!";
        
        newnode -> nextNode = NULL;
        //////////////여기까지가 만약 대여를 선택하였으 때 구조체에 저장된느 부분////////////////
        if(firstRentalInfoNode == NULL){
            firstRentalInfoNode = newnode;
            lastRentalInfoNode = newnode;
            RentalSize = RentalSize+1;
        }
        else{
            lastRentalInfoNode -> nextNode = newnode;
            lastRentalInfoNode = newnode;
            RentalSize = RentalSize+1;
        }
        printf(" 대열 정보 등록이 완료되었습니다.");
        
        return;
    }
    else if(RentalOrReturn == 2){ //반납 기능을 수행하는 함수
        
        char* rPersonName = malloc(sizeof(char)*30); // 검색하고 싶은 이름이 저장되는 문자열 변수
        RentalInfoNode *temp = firstRentalInfoNode; // temp에 firstdvdNode넣어준거
        printf(" 반납을 위해 대여 한 사람의 이름을 입력해주세요\n");
        scanf("%s", rPersonName);
        fflush(stdin);
        if(firstRentalInfoNode == NULL){// 하는거 아니야?? (내가 바꿔줘어써1
            
            printf("\n입력하신 이름의 사람은 대여한 dvd가 없습니다. \n");
            return;
        }
        ////////////////////////////
        if(!strcmp(firstRentalInfoNode->RpersonName,rPersonName)){// 첫번째 노드의 이름과 입력한 이름이 같을 경우
            firstRentalInfoNode = firstRentalInfoNode->nextNode;
            free(temp);
            RentalSize = RentalSize-1;
            printf("\n검색하신 dvd를 반납 처리 하였습니다.\n");
        }
        else{ // 첫번째에 검색한 정보와 일치하는 정보가 없을 경우
            
            RentalInfoNode* before = firstRentalInfoNode;
            while(1){
                if(!strcmp(temp->nextNode->RpersonName,rPersonName)){ // 두번째 노드 이 후부터 검색한 이름이 있는 경우(temp가 가르키는 다음 노드에 이름와 비교 )
                    // 문장열이 서로 같은 경우 strcmp()함수는 0을 반환한다.
                    RentalInfoNode *node_free = temp->nextNode; // (비교대상이 temp 다음
                    before -> nextNode = temp -> nextNode-> nextNode;// 노드이니까 삭제도 다음 노드가 삭제되어)
                    free(node_free);//
                    RentalSize = RentalSize-1;
                    printf("\n검색하신 dvd를 반납 처리 하였습니다.\n");
                    break;
                }
                else{
                    if(temp->nextNode == NULL){ // 다음에 손님정보에 대해 내가 입력한 값이라
                        printf("\n입력하시 이름으로 대여한 사람이 없습니다.. \n");// 비교하고 싶어도 더 이상
                        break;// 저장된 손님 정보가 없는 경우
                    }
                    before = before->nextNode;// 현재 손님 정보와 입력한 이름이 일치하지 않아서
                    temp = temp->nextNode;// 다음에 손님정보에서 검색하기위해 변수들의 값을 바꾸는 것이다.
                }
            }
        }
        return;
    }
    
}
// dvd 연체( 삭제 할 때 처럼 문자열을 strcmp를 이용해서 비교 후 대여 반납 처리를 한다.

// 현재 가게에서 대여 중인 정보를 모두 출력
void  RentalDvdInfoCheck(){
    int i = 0; // for문을 돌리기 위해 사용하는 변수
    RentalInfoNode *temp = malloc(sizeof(RentalInfoNode));
    temp = firstRentalInfoNode;
    printf("\n \n현재 대여 중인 dvd의 정보는 아래와 같습니다. \n");
    if( firstRentalInfoNode == NULL){
        printf("\n입력된  dvd 정보가 없어서 정보를 출력 할 수 없습니다. \n");
        return;
    }
    else{
        for(i ;  i < RentalSize ; i ++){
            printf("\n<-------------------->\n");
            printf("\n dvd 제목: %s\n" , temp->RdvdName);
            printf("\n dvd 빌린 사람 : %s\n", temp->RpersonName);
            printf("\n dvd 대여 날짜 : %d-%d-%d\n" , temp->Rdate[0], temp->Rdate[1], temp->Rdate[2] );
            printf("\n dvd 반납 날짜 : %d-%d-%d\n" , temp->ReturnDate[0], temp->ReturnDate[1], temp->ReturnDate[2]);
            printf("\n dvd 대여 현황 : %s\n" , temp->overDue);
            
            printf("\n<-------------------->\n");
            temp = temp->nextNode;
        }
    }
    
}

// 고급 검색(이름, 전화번호로 검색 기능 )
void Serching(){ // 특정회원에 이름으로 대여 정보를 확인
    char* rentalPersonName = malloc(sizeof(char)*30); // 검색하고 싶은 이름이 저장되는 문자열 변수
    RentalInfoNode *temp = firstRentalInfoNode; // temp에 firstdvdNode넣어준거
    printf("\n고객의 대여정보를 위해 이름을 입력해주세요\n");
    scanf("%s", rentalPersonName);
    fflush(stdin);
    if(firstRentalInfoNode == NULL){// 하는거 아니야?? (내가 바꿔줘어써1
        
        printf("\n<현재 매장에 대여 중인 dvd가 없습니다.> \n");
        return;
    }
    ////////////////////////////
    if(!strcmp(firstRentalInfoNode->RpersonName,rentalPersonName)){// 첫번째 노드의 이름과 입력한 이름이 같을 경우
        printf("\n검색하신 손님이 대여한 dvd정보는 아래와 같습니다.\n");
        printf("\n<-------------------->\n");
        printf("\n dvd 빌린 사람 : %s\n", temp->RpersonName);
        printf("\n dvd 제목: %s\n" , temp->RdvdName);
        printf("\n dvd 대여 날짜 : %d-%d-%d\n" , temp->Rdate[0], temp->Rdate[1], temp->Rdate[2] );
        printf("\n dvd 반납 날짜 : %d-%d-%d\n" , temp->ReturnDate[0], temp->ReturnDate[1], temp->ReturnDate[2]);
        printf("\n dvd 대여 현황 : %s\n" , temp->overDue);
        
        printf("\n<-------------------->\n");
        
    }
    else{ // 첫번째에 검색한 정보와 일치하는 정보가 없을 경우
        RentalInfoNode* before = firstRentalInfoNode;
        while(1){
            if(!strcmp(temp->nextNode->RpersonName,rentalPersonName)){ // 두번째 노드 이 후부터 검색한 이름이 있는 경우(temp가 가르키는 다음 노드에 이름와 비교 )
                // 문장열이 서로 같은 경우 strcmp()함수는 0을 반환한다.
                printf("\n검색하신 손님이 대여한 dvd정보는 아래와 같습니다.\n");
                printf("\n<-------------------->\n");
                printf("\n dvd 빌린 사람 : %s\n", temp->nextNode->RpersonName);
                printf("\n dvd 제목: %s\n" , temp->nextNode->RdvdName);
                printf("\n dvd 대여 날짜 : %d-%d-%d\n" , temp->nextNode->Rdate[0], temp->nextNode->Rdate[1], temp->nextNode->Rdate[2] );
                printf("\n dvd 반납 날짜 : %d-%d-%d\n" , temp->nextNode->ReturnDate[0], temp->nextNode->ReturnDate[1], temp->nextNode->ReturnDate[2]);
                printf("\n dvd 대여 현황 : %s\n" , temp->nextNode->overDue);
                
                printf("\n<-------------------->\n");
                break;
            }
            else{
                if(temp->nextNode == NULL){ // 다음에 손님정보에 대해 내가 입력한 값이라
                    printf("\n검색하신 손님은 대여한 dvd가 없습니다.\n");// 비교하고 싶어도 더 이상
                    break;// 저장된 손님 정보가 없는 경우
                }
                before = before->nextNode;// 현재 손님 정보와 입력한 이름이 일치하지 않아서
                temp = temp->nextNode;// 다음에 손님정보에서 검색하기위해 변수들의 값을 바꾸는 것이다.
            }
        }
    }
    return;
}
///////////////////////////////////  연체 관련 기능을 수행하는 함수//////////////////////////
void returnDelay(){ // 특정회원에 이름으로 검색 후 대여 정보를 연체 처리를 하는 함수
    char* rentalPersonName = malloc(sizeof(char)*30); // 검색하고 싶은 이름이 저장되는 문자열 변수
    int i = 0; // 가입된 손님 정보 갯수 만큰 for문 돌리기 위해 선언!
    int j = 0; // 대여 횟수 만큼 for을 돌리기 위해 선언!
    int returnDelay = 0;
    RentalInfoNode *temp = firstRentalInfoNode;//
    PersoonInfoNode *tempPerson = firstPersonNode; // 첫번째 가입 정보를 입력!!
    printf("\n고객의 대여 정보의 연체 처리를 위해 이름을 입력해주세요\n");
    scanf("%s", rentalPersonName);
    fflush(stdin);
    
    if(firstRentalInfoNode == NULL){// 하는거 아니야?? (내가 바꿔줘어써1
        
        printf("\n<현재 매장에서 대여해준 dvd가 없습니다.> \n");
        return;
    }
    ////////////////////////////
    for( j ;  j < RentalSize; j++){
        
        if(!strcmp(temp->RpersonName,rentalPersonName)){// 첫번째 노드의 이름과 입력한 이름이 같을 경우
            temp->overDue = "ReturnDelay";
            ////////////// 이름 찾기위한 for 문////////////////////////////////////
            for( i ; i < size; i++){ // i = 0 이니까 대여정보 구조체가 만들어진 횟수보다 1 적은 수를 비교해야한다.
                if(!strcmp(tempPerson->name,rentalPersonName)){// 첫번째 노드의 이름과 입력한 이름이 같을 경우
                    tempPerson->delayNumberOfTime +=1;
                    printf("\n검색하신 손님의 대여정보를 연체 처리하고 회원 정보에 연체 횟수를 '1' 증가 시켰습니다.\n");
                    returnDelay +=1;
                }
                tempPerson = tempPerson->nextNode;// 다음에 손님정보에서 검색하기위해 변수들의 값을 바꾸는 것이다.
                
            }
        }
        temp = temp->nextNode;
    }
    
    if((temp == NULL) && ( returnDelay == 0)){ // 다음에 손님정보에 대해 내가 입력한 값이라
        printf("\n현재 연체 중인 dvd는 없습니다.\n");// 비교하고 싶어도 더 이상
    }
    
    return;
}
/////////////////////////////////////////////////////////////////////

void serchingPersonInfo(){
    { // 특정회원에 가입 정보를 확인
        char* PersonName = malloc(sizeof(char)*30); // 검색하고 싶은 이름이 저장되는 문자열 변수
        PersoonInfoNode *temp = firstPersonNode; // temp에 firstdvdNode넣어준거
        printf("\n고객의 가입정보 확인을 위해 이름을 입력해주세요\n");
        scanf("%s", PersonName);
        fflush(stdin);
        if(firstPersonNode == NULL){// 하는거 아니야?? (내가 바꿔줘어써1
            
            printf("\n<매장에 가입된 손님이 없습니다.> \n");
            return;
        }
        ////////////////////////////
        if(!strcmp(firstPersonNode->name,PersonName)){// 첫번째 노드의 이름과 입력한 이름이 같을 경우
            printf("\n검색하신 손님이 가입 정보는 아래와 같습니다.\n");
            printf("\n<-------------------->\n");
            printf("\n 이름 : %s\n" , temp->name);
            printf("\n 번호 : %d\n", temp->Phone);
            printf("\n 연체 횟수 : %d회\n", temp->delayNumberOfTime);
            printf("\n<-------------------->\n");
            
        }
        else{ // 첫번째에 검색한 정보와 일치하는 정보가 없을 경우
            while(1){
                if(!strcmp(temp->nextNode->name,PersonName)){ // 두번째 노드 이 후부터 검색한 이름이 있는 경우(temp가 가르키는 다음 노드에 이름와 비교 )
                    // 문장열이 서로 같은 경우 strcmp()함수는 0을 반환한다.
                    printf("\n검색하신 손님이 가입 정보는 아래와 같습니다.\n");
                    printf("\n<-------------------->\n");
                    printf("\n 이름 : %s\n" , temp->nextNode->name);
                    printf("\n 번호 : %d\n", temp->nextNode->Phone);
                    printf("\n 연체 횟수 : %d회\n", temp->nextNode->delayNumberOfTime);
                    printf("\n<-------------------->\n");
                    break;
                }
                else{
                    if(temp->nextNode == NULL){ // 다음에 손님정보에 대해 내가 입력한 값이라
                        printf("\n검색하신 손님 회원가입을 한 적이 없습니다.\n");// 비교하고 싶어도 더 이상
                        break;// 저장된 손님 정보가 없는 경우
                    }
                    temp = temp->nextNode;// 다음에 손님정보에서 검색하기위해 변수들의 값을 바꾸는 것이다.
                }
            }
        }
        return;
    }
}


//연체 중인 dvd 대여 정보 출력
void DelayPerson(){
    char* status = malloc(sizeof(char)*30);
    //
    int i = 0;
    int printNumberOfTime = 0;
    RentalInfoNode *temp = firstRentalInfoNode; //
    status = "ReturnDelay"; //
    if(firstRentalInfoNode == NULL){// 하는거 아니야?? (내가 바꿔줘어써1
        
        printf("\n<현재 매장에 대여 중인 dvd가 없습니다.> \n");
        return;
    }
    ////////////////////////////
    for( i ; i < RentalSize; i++){ // i = 0 이니까 대여정보 구조체가 만들어진 횟수보다 1 적은 수까지 반복해야한다.
        if(!strcmp(temp->overDue,status)){// 첫번째 노드의 이름과 입력한 이름이 같을 경우
            printf("\n 현재 연체 중인 dvd의 대여 정보는 아래와 같습니다.\n");
            printf("\n<-------------------->\n");
            printf("\n dvd 빌린 사람 : %s\n", temp->RpersonName);
            printf("\n dvd 제목: %s\n" , temp->RdvdName);
            printf("\n dvd 대여 날짜 : %d-%d-%d\n" , temp->Rdate[0], temp->Rdate[1], temp->Rdate[2] );
            printf("\n dvd 반납 날짜 : %d-%d-%d\n" , temp->ReturnDate[0], temp->ReturnDate[1], temp->ReturnDate[2]);
            printf("\n dvd 대여 현황 : %s\n" , temp->overDue);
            printf("\n<-------------------->\n");
            printNumberOfTime += 1;
        }
        temp = temp->nextNode;// 다음에 손님정보에서 검색하기위해 변수들의 값을 바꾸는 것이다.
    }
    ///// 연체 중인 dvd를 만나면 해당 정보만 출력하고 끝낸다. 반복문을 사용하여 연체 dvd전부를 출력하자/////////////
    if((temp == NULL)&&(printNumberOfTime ==0)){ // 연체한 사람이 없으면 연체 리스트에 출력 횟수도 0이고 temp도 끝가지 다 돌았을것이다.
        printf("현재 연체된 dvd는 없습니다..\n");// 비교하고 싶어도 더 이상
    }// 저장된 손님 정보가 없는 경우}
    return;
    
}


// 블랙 리스트 ( 상습연체 고객 리스트 )관리 , 및 화면!! 삼진 아웃제도임
void Blacklist(){
    int i = 0; // for문을 돌리기 위해 사용하는 변수
    PersoonInfoNode *temp = malloc(sizeof(PersoonInfoNode));
    temp = firstPersonNode;
    printf(" \n현재 Black List에 등록된 손님의 정보는 아래와 같습니다. \n");
    if( firstPersonNode == NULL){
        printf("\n저장된 손님 정보가 없어서 정보를 출력 할 수 없습니다. \n");
        return;
    }
    else{
        for(i ;  i < size ; i ++){
            if(temp->delayNumberOfTime >= 4 ){
                printf("\n<-------------------->\n");
                printf("\n 이름 : %s\n" , temp->name);
                printf("\n 번호 : %d\n", temp->Phone);
                printf("\n 연체 횟수 : %d회\n", temp->delayNumberOfTime);
                printf("\n<-------------------->\n");
            }
            temp = temp->nextNode;
        }
    }
    
}
// 모든 정보 파일로 저장(고객정보, DVD 보유 정보, DVD 대여정보 및 연체정보))
void WordInText(){
    
}

//////////// mina/////////////////////////
int main(int argc, const char * argv[]) {
    // insert code here...
    int madeOrDelete = 0;
    int menu = 1; // while문 조건을 위해 선언함
    int select = 0;
    while(menu){
        printf("\nDVD 대여 프로그램입니다. 아래에 원하는 메뉴를 입력해주세요 !\n");
        printf("<<<<<<<아래에서 원하는 기능이 있으면 입력해주세요>>>>>>>\n");
        printf("\n1번 : 고객 정보 괸련 기능 \n");
        printf("2번 : dvd 정보 관련 기능 \n");
        printf("3번 : dvd 대여, 반납, 연체 관련 기능 \n");
        printf("5번 : 프로그램 종료 ");
  
        scanf("%d", &select);
            fflush(stdin);
        //////////////////////////////////////////////////
       if(select == 1){
           printf("회원에 관련된 기능중 원하는 기능을 입력해주세 \n");
           printf("\n1 : 신규 회원 등록\n");
           printf("2 : 기존 회원 중 삭제\n");
           printf("3 : 현재 저장된 손님 정보 출력 \n");
           printf("4 : 회원 정보 검색( 이름으로 검색! ) \n");
           printf("5 : 블랙 리스트 출력하기( 삼진아웃제도 ) \n");
           
                scanf("%d", &madeOrDelete);
                    fflush(stdin);
           if(madeOrDelete == 1){
               Personinfo();// 이름에 &
               madeOrDelete = 0;
               
           }
           else if(madeOrDelete == 2){ // 이 부분에 삭제에 관한 함수 입력해줘야 한다.
               PersoninfoDelete();// 이름에 &
               madeOrDelete = 0;
               
           }
           else if(madeOrDelete == 3){
               personInfoCheck();
               madeOrDelete = 0;
               
           }
            else if(madeOrDelete == 4){// 이 부분에  이름통해 검색하는 기능을 넣을 것!!
                serchingPersonInfo();
                madeOrDelete = 0;
            }
           else{
               Blacklist();
               madeOrDelete = 0;
               
           }
           select = 0 ; // 다시 0 으로 만들어주여서 나중에서  언하는 값을 넣을수 있도록 초기화 해줌
           
        }
        ///////////////////////////////////////////////////////
        else if(select == 2){
            printf("\ndvd에 관련된 기능중 원하는 기능을 입력해주세 \n");
            printf("\n1 : 신규 dvd 정보 등록\n");
            printf("2 : 삭제하고 하는 dvd 삭제, \n");
            printf("3 : 현재 저장된 dvd 정보 출력 \n");
            
            scanf("%d", &madeOrDelete);
            fflush(stdin);
            if(madeOrDelete == 1){
                dvdInfo();// 이름에 &
                madeOrDelete = 0;
                
            }
            else if(madeOrDelete == 2){ // 이 부분에 삭제에 관한 함수 입력해줘야 한다.
                dvdInfoDelete();// 이름에 &
                madeOrDelete = 0;
                
            }
            else{
                dvdInfoCheck();
                madeOrDelete = 0;
                
            }
            select = 0 ; // 다시 0 으로 만들어주여서 나중에서  언하는 값을 넣을수 있도록 초기화 해줌
            
            

       
        }
        else if(select == 3){
            printf("\ndvd 대여, 연체, 반납 관련된 기능중 원하는 기능을 입력해주세요 \n");
            printf("\n1 : dvd 대여/반납 기능 \n");
            printf("2 : 현재 대여중인 dvd 정보 모두 보기  \n");
            printf("3 : 특정 회원의 대여 정보  \n");
            printf("4 : 특정 회원의 연체 처리하기  \n");
            printf("5 : 연체된 dvd의 대여 정보 출력  \n");
            
            
            scanf("%d", &madeOrDelete);
            fflush(stdin);
            if(madeOrDelete == 1){
                RentalDvdInfo();// 이름에 &
                madeOrDelete = 0;
                
            }
            else if(madeOrDelete == 2){ // 이 부분에 대여 정보 관한 함수 입력해줘야 한다.
                RentalDvdInfoCheck();// 이름에 &
                madeOrDelete = 0;
                
            }
            else if(madeOrDelete == 3){
                 Serching();
                 madeOrDelete = 0;
            }
            else if(madeOrDelete == 4){
                returnDelay();
                madeOrDelete = 0;
            }
            else{
                DelayPerson();
                madeOrDelete = 0;// 연체자 리스트 출력 함숭
            }
              select = 0 ; // 다시 0 으로 만들어주여서 나중에서  언하는 값을 넣을수 있도록 초기화 해줌
        }
        
        else {
             
            return 0; // 프로그램 종료를 위해 return으로 0을 반환하는 것이야
            
        }
     
    }
    return 0;
}
