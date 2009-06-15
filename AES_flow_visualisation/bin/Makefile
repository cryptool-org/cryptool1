all: Gf28.class State.class DrawScheme.class RijndaelView.class MainView.class Test.class RijndaelApplet.class

CLASSPATH = .:/usr/lib/jdk1.1.8/lib/classes.zip

# JAVAC = jikes -classpath $(CLASSPATH)
JAVAC = javac -deprecation

%.class: %.java
	$(JAVAC)  $*.java
