
#include "InformationPoint.h"
#include "InformationLine.h"
#include "InformationPolygon.h"

#ifndef _INFORMATION_
#define _INFORMATION_


#define NAME_SIZE 64

//부모

class Information{

private:
	
	bool initFlag;
	bool parentClickedFlag;
	//char parentName[NAME_SIZE];	//부모이름
	int numberOfChild;			//자식의 갯수. 이것을 알면 점, 선, 원, 다각형의 vector 어레이 이용 가능

	
	
	vector<bool> clickedChild;							//클릭된 자식 노드 정보 가지고 있음


	//여기에 선0
	//여기에 원
	//여기에 다각형

public:
	vector<InformationPoint> pointClass;				//배열처럼 사용.   0번쨰는 첫번째 자식이 가지고 있는 점들의 정보. 1은 두번쨰 자식..
	vector<InformationLine> linesClass;
	vector<InformationPolygon> polygonsClass;			//폴리곤 클래스

	//초기화자
	Information();
	Information(bool init);

	//set 함수 및 update 함수
	void setInformationFromFile(char* fileName);	//파일명으로부터 정보 받아옴..
	void setNumberOfChild(int number);
	void setInformationSize(int number);
	void updateInformationFile(char* fileName); //파일 업데이트
	void setIsChildClicked(int index, bool flag);
	void setIsParentClicked(bool flag);  

	int getNumberOfChild(void);		//자식노드의 수 반환
	bool isChildClicked(int index);		//해당 index 의 자식노드가 클릭 되었는지 여부 리턴
	bool isParentClicked(void);		//부모노드 활성화 중인지 여부 리턴
	char* getParentName(void);		//이름 반환


	//액셀로 부터 데이터 읽어오기
	//새로운 내용 저장하기		//새로운 내용 시작 인덱스 필요 ex) 점의경우 아이디 123번까지가 기존의 데이터를 읽었었는데, 124번째 부터라면, 123이라는 인덱스를 가지고 있어야함..
								//								 만약에 기존 데이터를 수정할 경우..는 문제가 안되고 삭제할 경우, 해당 아이디값을 음수로 주고, 이 상태에서 데이터 추가하였을 기
								//								 삭제된 부분에 채워 넣는 것이 아니라, 그냥 뒤에다가 연결 시킨다. 그리고 저장할 때 음수인 아이디 값은 무시하고 땡겨서 저장하면 될것!! 
	

};


#endif