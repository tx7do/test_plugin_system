# 测试插件系统

插件系统主要就是加载动态库，然后调用动态库的接口，进行插件的加载和使用。

历史悠久的COM就是一种插件系统。

## 安装依赖库

安装Boost

```bash
sudo apt-get install libboost-all-dev
```

安装POCO

```bash
sudo apt-get install libpoco-dev
```

## 基于Boost.DLL的插件系统

Boost和STL差不多是一个模板库，它提供了Boost.DLL的接口，可以让我们在C++中方便的实现插件系统。

## 基于POCO.ClassLoader的插件系统

POCO是一个仿造Java和.net的类库，它提供了一个类库加载器，可以加载类库，并且可以获取类库的信息。

## 从Ogre中提取的插件系统

Ogre是我刚开是工作的时候读过的开源项目中的其中一个，对我影响很深。它是基于插件系统的，所以很灵活。
