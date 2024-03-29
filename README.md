# I A Happier Than You
English Version

<aside>
💡 项目施工中

</aside>

目前可玩版本请下载main Branch

追踪最新开发进度请下载NewDev Branch

这个项目是一个基于UE5 C++开发的双人本地回合制游戏原型框架，有基本的博弈机制可供完整游玩，同时适合初学UE5以及UE5 C++的同好学习入门。

# 项目特色

## 可玩性

本游戏是双人本地回合制游戏，如果您有游戏搭子或者足够无聊，本游戏有一个完整的数学框架提供了一个类似于桌游的游玩体验，具有一定的博弈性。游戏的设计思路以及基本规则，可在以下文档中查看：

[I Am Happier Than You](https://www.notion.so/I-Am-Happier-Than-You-1a21dd7046bf48849d51ba5903ec01ab?pvs=21) 

## AI辅助编程

游戏的开发过程利用了AI的帮助，能够合理使用AI是目前程序员必备的能力之一，可以极大地提高开发效率，本项目合理利用了 GPT-4 和 Github Copilot。

具体的开发记录可查看以下文档：

[AI-assisted Game Prototyping](https://www.notion.so/AI-assisted-Game-Prototyping-9ce7b110bafd423da906774c602bcf9f?pvs=21) 

## 合理解耦

较大的游戏项目，比如UE5官方的Lyra，或者Tom Looman的课程项目ActionRougelike，游戏各部分的解耦往往将游戏逻辑打散到了项目的各部分，使得初学者很难在短时间内理清思路。

本项目由于规模较小，在功能解耦方面取得了相对的平衡，使得代码更易阅读。项目的类UML文档如下：

## 可扩展性

在维持游戏的基本框架下，具有相当的可扩展性，可以自由设置物品信息，改变游戏机制。

## 注释完整

本项目代码有完整中英文注释。

## UMG Widget

UMG Widget是一个很强大的UI工具链，没有必要UI也使用C++来实现，这样反而会不灵活。
