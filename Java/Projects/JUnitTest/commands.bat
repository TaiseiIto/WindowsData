javac MyCar.java
javac -classpath .;../../jar/hamcrest-core-1.3.jar;../../jar/junit-4.12.jar MyCarTest.java
java -classpath .;../../jar/hamcrest-core-1.3.jar;../../jar/junit-4.12.jar org.junit.runner.JUnitCore MyCarTest