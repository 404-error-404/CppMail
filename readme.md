# SMTP动态链接库说明
整个工程下边包含三个项目，分别是：
- **CppMail** C++实现SMTP协议的封装类，里边包含了本次SMTP协议实现的所有相关功能
- **Dll1** 将上述类封装进DLL，并且再封装一个供前端调用的函数

  项目的启动位置设置成了下边项目生成的exe以便调试，所以直接启动会报错，在`项目属性→调试→命令`中把`$(TargetPath)`改成exe的所在路径即可

  【因为初期未找到如何用C++开发托管的DLL，所以额外封装了一个函数，但功能实现之后发现官方文档有一个示例，由于时间关系（也怕再踩坑）就没有再去实现，希望之后有人能够看一看】


- **WindowsFormsApp1** 一个特别简单的前端代码，里边演示了如何调用DLL并发送邮件
