package ru.spbstu;

public class Obfuscator {

    public static void main(String[] args) {
	    final String stringToEncrypt = args[0];
	    Encryptor encryptor = new Encryptor();
	    final String encryptedString = encryptor.encryptStr(stringToEncrypt);
	    System.out.println(encryptedString);
    }
}
