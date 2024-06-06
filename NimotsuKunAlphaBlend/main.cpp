#include "GameLib/Framework.h"
using namespace GameLib;

#include "State.h"
#include "File.h"

//�֐��v���g�^�C�v
void mainLoop();

//�O���[�o���ϐ�
State* gState = 0;

//���[�U�����֐��B���g��mainLoop()�Ɋۓ���
namespace GameLib{
	void Framework::update(){
		mainLoop();
	}
}

void mainLoop(){
	//�~�{�^��������Ă�H
	if ( Framework::instance().isEndRequested() ){
		if ( gState ){
			delete gState;
			gState = 0;
		}
		return;
	}
	//�ŏ��̃t���[���͏������B�ŏ��̏�Ԃ�`�悵�ďI���B
	if ( !gState ){ 
		File file( "stageData.txt" );
		if ( !( file.data() ) ){ //�f�[�^�Ȃ��I
			cout << "stage file could not be read." << endl;
			return;
		}
		gState = new State( file.data(), file.size() );
		//����`��
		gState->draw();
		return; //���̂܂܏I���
	}
	bool cleared = false;
	//���C�����[�v
	//�N���A�`�F�b�N
	if ( gState->hasCleared() ){
		cleared = true;
	}
	//���͎擾
	cout << "a:left d:right w:up s:down. command?" << endl; //�������
	char input;
	cin >> input;
	//�I������
	if ( input == 'q' ){
		delete gState;
		gState = 0;
		Framework::instance().requestEnd();
		return;
	}
	//�X�V
	gState->update( input );
	//�`��
	gState->draw();

	if ( cleared ){
		//�j���̃��b�Z�[�W
		cout << "Congratulation! you win." << endl;
		delete gState;
		gState = 0;
	}
}

