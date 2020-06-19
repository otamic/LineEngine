1	运行环境
	软件	Windows7及以上操作系统
			Visual Studio 2013 及以上版本
			
2	工程结构
	LineEngine
	｜--Libraris				依赖库
		｜--includes
		｜--libs
	｜--src					源代码
		｜--build			构建项目位置
		｜--Engine			引擎及相关代码
		｜--game.cpp		用户填充代码
	｜--CMakeLists.txt		项目建立文件
	
3	项目构建
	本项目使用CMake构建，关于CMake更多内容访问：https://cmake.org/
	
	构建过程
		以下在Window7和Visual Studio 2013为例
		使用CMake图形界面，设置代码目录为：LineEngine，构建目录为：LineEngine/src/build，点击Configure选择Visual Studio 2013，点击Finish，会看见中间出现红色条目；
		再次点击Configure，红色条目消失；点击Generate生成项目；点击Open Project打开项目
		生成解决方案GAME，下有四个项目：ALL_BUILD，Engine，GAME，ZERO_CHECK，其中ALL_BUILD和ZERO_CHECH是CMake管理项目相关，可以移除；Engine则包含引擎相关代码，GAME则是给用户填充部分。
		把GAME设置为启动项目。
		打开GAME的属性页，在配置属性/连接器/系统页面上，子系统设置为：控制台
		项目构建完毕。
		
4	项目使用
	打开在GAME项目下的game.cpp文件
	可以看见项目引入了所写的引擎库
	
	1.  #include <engine.h>  

	对引擎库的使用是通过继承方式实现
	
	class Game :public Engine {  
		
	在继承时可设置窗口名，以及窗口的宽高。完整的继承方式
	
	class Game :public Engine（string name, int width, int height) {  
		
	在成员函数部分设置，添加所需要的类。例：
	
	1.	// declare members hear  
	2.	Camera * camera;  
	3.	GameObject * gameObject; 
	
	接下来初始化，在这里填充游戏运行前所需的设定
	
	1.	void Init() {  
	2.	    // initialize members  
	3.	} 
	
	接下来是对输入的处理，这个是可选的，可以把该部分代码放入下一个模块。传入参数dt是距上一次刷新的间隔
	
	1.	void ProcessInput(float dt) {  
	2.	    // optimal, can move all codes to Update  
	3.	    // process any inputs hear  
	4.	}  
	
	最后就是定义游戏的部分，传入参数dt同样是距上一次刷新的间隔
	
	1.	void Update(float dt) {  
	2.	    // define the game logic hear  
	3.	}  
	
	最后想要游戏可以运行，还需要设置
	
	DECLEARE_MAIN(Game) 

	一个完整的演示如下：
	1.	#include "engine.h"  
	2.	  
	3.	class Game :public Engine("Demo", 800, 600) {  
	4.	    Camera * camera;  
	5.	    GameObject * gameObject;  
	6.	  
	7.	    void Init() {  
	8.	        // set game status  
	9.	        Frame = LOCK30;  
	10.	        // set camera  
	11.	        camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));  
	12.	        camera->Type = FPS;  
	13.	        BindCamera(camera);  
	14.	        // set object  
	15.	        gameObject = new GameObject("AA", glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0, 1.0f, 0.0f));  
	16.	        gameObject->BindResources("ship1.obj");  
	17.	        BindObject(gameObject);  
	18.	        // set music  
	19.	        std::string music = "ophelia.mp3";  
	20.	        PlayMusic(music, true);  
	21.	    }  
	22.	  
	23.	    void ProcessInput(float dt) {  
	24.	        // set camera  
	25.	        if (this->Keys[GLFW_KEY_W] == GLFW_PRESS)  
	26.	            camera->ProcessKeyboard(FORWARD, dt);  
	27.	        if (this->Keys[GLFW_KEY_S] == GLFW_PRESS)  
	28.	            camera->ProcessKeyboard(BACKWARD, dt);  
	29.	        if (this->Keys[GLFW_KEY_A] == GLFW_PRESS)  
	30.	            camera->ProcessKeyboard(LEFT, dt);  
	31.	        if (this->Keys[GLFW_KEY_D] == GLFW_PRESS)  
	32.	            camera->ProcessKeyboard(RIGHT, dt);  
	33.	  
	34.	        if (this->CurMoved)  
	35.	            camera->ProcessMouseMovement(Xoffset, Yoffset);  
	36.	    }  
	37.	  
	38.	    void Update(float dt) {  
	39.	        // add object a speed  
	40.	        gameObject->Position.z += 0.01f;  
	41.	    }  
	42.	};  
	43.	  
	44.	DECLARE_MAIN(Game)
	
	  
附录：软件接口
class GameObject

public attributes
string Name	物体名称
bool Visible	物体是否可见
vec3 Position	物体位置
vec3 Scale	物体缩放
vec3 Color	物体颜色
vec3 Rotation	物体朝向
Model * Resources	绑定的素材



public functions
GameObject()	默认构造函数
GameObject(string name, vec3 pos, vec3 scale, vec3 color)	构造函数
bool BindResources(const string & path)	绑定素材
virtual void Draw(Shader & shader, Camera & camera, float ratio)	绘制物体

GameObject()
传入参数	描述
无	
返回	描述
GameObject	构造的GameObject类
功能	构造一个使用默认参数的类
默认的名称“default”，位置为原点，没有缩放，白色，没有旋转

GameObject(string name, vec3 pos, vec3 scale, vec3 color)
传入参数	描述
string name	物体的名称
vec3 pos	物体位置
vec3 scale	物体缩放
vec3 color	物体颜色
输出	描述
GameObjece	构造的GameObject类
功能	通过传递参数构造一个物体

bool BindResources(const string & path)
传入参数	描述
const string & path	素材的路径
输出	描述
bool	是否正确绑定
功能	通过路径绑定一个素材
常见的模型格式例如Obj等都可以绑定

virtual void Draw(Shader & shader, Camera & camera, float ratio)
传入参数	描述
Shader & shader	着色器
Camera & camera	相关的相机
float ratio	屏幕的长宽比
输出	描述
无	
功能	用户无需了解这个函数
函数用来绘制物体


class Camera

definitions
enum Camera_Movement	描述相机位置
可选项有：
FORWARD
BACKWARD
LEFT
RIGHT
enum Camera_Type	描述相机类型
可选项有：
NORMAL
FPS
const float YAM = -90.0f	默认转角
const float PITCH = 0.0f	默认仰角
const float SPEED = 2.0f	默认速度
const float SENSITIVITY = 0.1f	默认鼠标灵活度
const float ZOOM = 45.0f	默认视角

public attributes
vec3 Postion	相机位置
vec3 Front	前向量
vec3 Up	上向量
vec3 Right	右向量
vec3 WorldUp	世界上向量
float Yam	转角
float Pitch	仰角
float MovementSpeed	移动速度
float MouseSensitivity	鼠标灵活度
float Zoom	视角
Camera_Type Type	相机类型
float lockY	锁定的高度（FPS类型）
public functions
Camera()	默认构造函数
Camera(
float posX,
float posY,
float posZ,
float upX,
float upY,
float upZ,
float yaw,
flaot pitch)	构造函数
mat4 GetViewMatrix()	生成变换矩阵
void ProcessKeyboard(
Camera_MoveMent direction, 
float deltaTime)	（键盘）控制相机移动
void ProcessMouseMovement(
float xoffset,
float yoffset)	（鼠标）控制相机转角
void ProcessMouseScroll(float yoffset)	（滚轮）控制相机视角

Camera()
传入参数	描述
无	
返回	描述
Camera	构造的Camera类
功能	构造一个使用默认参数的类
默认参数使用全局变量

Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
传入参数	描述
float posX	位置的X坐标
float posY	位置的Y坐标
float poxZ	位置的Z坐标
float upX	上向量的X坐标
float upY	上向量的Y坐标
float upZ	上向量的Z坐标
float yaw	转角
float pitch	仰角
返回	描述
Camera	构造的Camera类
功能	通过传递参数构造相机

mat4 GetViewMatrix()
传入参数	描述
无	
返回	描述
mat4	变换举证
功能	通过相机参数构造变换矩阵

void ProcessKeyboard( Camera_MoveMent direction, float deltaTime)
传入参数	描述
Camear_MoveMent direction	方向
float deltaTime	时间间隔
返回	描述
无	
功能	此函数为辅助控制相机所用
推荐通过键盘控制
通过描述方向和刷新时间来控制相机的移动，改变参数

void ProcessMouseMovement(float xoffset, float yoffset)
传入参数	描述
float xoffset	鼠标X轴上的位移
float yoffset	鼠标X轴上的位移
返回	描述
无	
功能	此函数为辅助控制相机所用
推荐通过鼠标控制
通过鼠标的移动控制相机的转角，改变参数

void ProcessMouseScroll(float yoffset)
传入参数	描述
float yoffset	鼠标滚轮的移动
返回	描述
无	
功能	此函数为辅助控制相机所用
推荐通过鼠标控制
通过鼠标滚轮的移动控制相机的视角大小，改变参数


class Engine

definitions
enum GameStatus	描述游戏状态
可选项有：
GAME_ACTIVE
GAME_MENU
enum GameFrame	描述游戏的刷新率
可选项有：
LOCK30
LOCK60
NO_LOCK

public attributes
int ScreenWidth	窗口宽度
int ScreenHeight	窗口高度
GameStatus Status	游戏状态
GameFrame Frame	游戏刷新率
bool Keys[1024]	键盘状态
bool Mouse[8]	鼠标按键状态
bool CurMoved	鼠标移动状态
float Xoffset	鼠标X轴位置
float Yoffset	鼠标Y轴位置

protected attributes
Shader * DefaultShader	默认着色器

public functions
Engine(string name, int width, int height)	构造函数
void Create()	构建流程所需函数，用户无需了解
void Run()	构建流程所需函数，用户无需了解
virtual void Init() = 0	初始化函数
virtual void ProcessInput(float dt)	处理输入函数
virtual void Update(float dt) = 0	定义游戏逻辑函数
virtual void Render();	渲染函数，用户无需了解

Engine(string name, int width, int height)
传入参数	描述
string name	名称
int width	屏幕宽度
int height	屏幕高度
返回	描述
Engine	构造的Engine类
功能	通过参数构造引擎

virtual void Init() = 0
传入参数	描述
无	
返回	描述
无	
功能	用户实现，用以初始化用户数据

virtual void ProcessInput(float dt)
传入参数	描述
flaot dt	画面刷新间隔
返回	描述
无	
功能	用户可选实现，用以初始化处理输入

virtual void Update(float dt) = 0
传入参数	描述
flaot dt	画面刷新间隔
返回	描述
无	
功能	用户实现，用以定义游戏逻辑

protected functions
void BindCamera(Camera * camera)	绑定相机
void BindObject(GameObject * object)	绑定物体
void PlayMusic(string path, bool isRepead)	播放音乐

void BindCamera(Camera * camera)
传入参数	描述
Camera * camera	需要绑定相机
返回	描述
无	
功能	绑定相机

void BindObject(GameObject * object)
传入参数	描述
GameObject * object	需要绑定的物体
返回	描述
无	
功能	绑定需要渲染的物体

void PlayMusic(string path, bool isRepead)
传入参数	描述
string path	音乐文件路径
bool isRepead	是否重复播放
返回	描述
无	
功能	播放音乐

