/*INF2102 Projeto Final de Programação*****************
 *Período: 2012/2
 *Coordenador: Prof. Carlos José Pereira Lucena       *
 *Projeto: Media-Preview Plugin para o Composer 3.0   *
 *Nome do aluno: Amparito Alexandra Morales Figueroa. *
 *Matrícula: 1121838                                  *
 *Orientador: Prof. Luiz Fernando Gomes Soares        *
 *Classe: AudioPlayer                                 *
 *Descrição: Exibição de mídias de audio***************/

#include <audioplayer.h>
#include<QObject>
#include<QPushButton>
#include<MediaObject>
#include<QWidget>
#include<QMouseEvent>
#include<QHBoxLayout>
#include<VideoPlayer>
#include<QFont>
#include<AudioOutput>
#include<QSlider>
#include<VolumeSlider>
#include<Path>

audioplayer::audioplayer(QString filename)

{
  setStyleSheet("* { background-color: rgb(220,220,220) }");
  setMinimumWidth(150);
  setMinimumHeight(60);

  mediaobject = Phonon::createPlayer(Phonon::MusicCategory,
                                     Phonon::MediaSource(filename));
 /*Criação dos botões de controle(play, pause, stop, slider de voulme,e
  seek slider*/

  playButton = new QPushButton();
  pauseButton = new QPushButton();
  stopButton = new QPushButton();
  playButton->setFont(QFont("Comic Sans MS",10,QFont::Bold));
  pauseButton->setFont(QFont("Comic Sans MS",10,QFont::Bold));
  stopButton->setFont(QFont("Comic Sans MS",10,QFont::Bold));

  playButton->setIcon(QIcon("play.jpeg"));
  playButton->setFixedWidth(51);
  playButton->setFixedHeight(34);
  playButton->setIconSize(QSize (26,26));
  playButton->setStyleSheet("* { background-color: rgb(173,255,47) }");
  playButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

  pauseButton->setIcon(QIcon("pause.jpeg"));
  pauseButton->setFixedWidth(51);
  pauseButton->setFixedHeight(34);
  pauseButton->setIconSize(QSize (26,26));
  pauseButton->setStyleSheet("* { background-color: rgb(173,255,47) }");
 pauseButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

 stopButton->setIcon(QIcon("stop.jpeg"));
  stopButton->setFixedWidth(51);
  stopButton->setFixedHeight(34);
  stopButton->setIconSize(QSize (26,26));
  stopButton->setStyleSheet("* { background-color: rgb(173,255,47) }");
stopButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

  mediaobject = new Phonon::MediaObject(this);
  mediaobject->setCurrentSource(Phonon::MediaSource(filename));
  Audioutput =new Phonon::AudioOutput(Phonon::MusicCategory, this);
  audioOutputPath = Phonon::createPath(mediaobject, Audioutput);
     Audioutput->setVolume(0.003);

   volumeslider= new Phonon::VolumeSlider();
   volumeslider->setAudioOutput(Audioutput);

   volumeslider->setSingleStep(0.002);
   volumeslider->setMaximumVolume(0.5);
   volumeslider->setTracking(true);
   volumeslider->setMaximumVolume(1);
   volumeslider->setMuteVisible(true);
   volumeslider->setFixedSize(150,31);
   volumeslider->setFixedWidth(170);
   volumeslider->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::MinimumExpanding);



   Phonon::SeekSlider *slider = new Phonon::SeekSlider;
   slider->setMediaObject(mediaobject);
   slider->setFixedWidth(510);
   slider->show();


  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(playButton);
  layout->addWidget(pauseButton);
  layout->addWidget(stopButton);
  layout->addWidget(volumeslider);

  QHBoxLayout *layout2=new QHBoxLayout;
  layout2->addWidget(slider);

 QVBoxLayout *layoutf=new QVBoxLayout;

 layoutf->addLayout(layout);
 layoutf->addLayout(layout2);

setLayout(layoutf);

setVisible(true);


/*Slots para o controle dos botões*/

QObject::connect(playButton,SIGNAL(clicked()),this,SLOT(play()));
QObject::connect(pauseButton,SIGNAL(clicked()),this,SLOT(pause()));
QObject::connect(stopButton,SIGNAL(clicked()),this,SLOT(stop()));

}


audioplayer::~audioplayer()
{

}

void audioplayer::play()
{
  mediaobject->play();

}

void audioplayer::pause()
{
  mediaobject->pause();
}

void audioplayer::stop()
{
  mediaobject->stop();
}







