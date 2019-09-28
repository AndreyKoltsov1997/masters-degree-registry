package ru.spbstu;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.UnsupportedEncodingException;
import java.util.Base64;

/**
 * Performcs encryption using AES algorithm.
 */
public class Encryptor {
    private static final String ENCRYPTION_ALGORITHM = "AES";
    /**
     * @param INITIALIZATION_VECTOR - initialization vector for CBC encryption.
     */
    private final String INITIALIZATION_VECTOR = "spbstu-data-analysis";
    private final String ENCRYPTION_KEY = "spbstu-encryption-key";
    private final String BASIC_ENCODING_TYPE = "UTF-8";


    public Encryptor() { }

    /**
     * Encrypts @param stringForObfuscation using AES algorithm with CBS mode.
     * @return encrypted string.
     */
    public final String encryptStr(final String stringForObfuscation) {
        String result = "";
        try {
            Cipher cipherEncryptionHandler = this.generateCipherEncryptionHandler(this.BASIC_ENCODING_TYPE, Cipher.ENCRYPT_MODE);
            byte[] encryptedValue = cipherEncryptionHandler.doFinal(stringForObfuscation.getBytes());
            result = Base64.getEncoder().encodeToString(encryptedValue);
        } catch (Exception error) {
            System.err.println("Unable to encrypt string: " + stringForObfuscation);
            error.printStackTrace();
            return null;
        }
        return result;
    }

    /**
     * @param obfuscatedString - string to be decrypted.
     * @return decrypted string.
     */
    public final String decryptStr(final String obfuscatedString) {
        String result = "";
        try {
            Cipher cipherEncryptionHandler = this.generateCipherEncryptionHandler(this.BASIC_ENCODING_TYPE, Cipher.DECRYPT_MODE);
            byte[] decodedRawValue = cipherEncryptionHandler.doFinal(Base64.getDecoder().decode(obfuscatedString));
            result = new String(decodedRawValue);
        } catch (Exception error) {
            System.err.println("Unable to decode string: " + obfuscatedString);
            error.printStackTrace();
        }
        return result;
    }

    // MARK: - Private

    private Cipher generateCipherEncryptionHandler(final String encodingType, int mode) {
        Cipher cipherEncryptionHandler = null;
        try {
            // NOTE: Specification of initialization vector.
            IvParameterSpec initVectorParameterSpec = new IvParameterSpec(this.INITIALIZATION_VECTOR.getBytes(encodingType));
            SecretKeySpec secretKeySpec = new SecretKeySpec(this.ENCRYPTION_KEY.getBytes(encodingType), Encryptor.ENCRYPTION_ALGORITHM);

            final String cipherAlgorithmTransformation = "AES/CBC/PKCS5PADDING";
            cipherEncryptionHandler = Cipher.getInstance(cipherAlgorithmTransformation);
            cipherEncryptionHandler.init(Cipher.ENCRYPT_MODE, secretKeySpec, initVectorParameterSpec);
        } catch (UnsupportedEncodingException error) {
            System.err.println("Unable to create Cipher Encryption handler due to an unsupported encoding: " + encodingType);
            return null;
        } catch (Exception error) {
            System.err.println("Unable to create Cipher Encryption handler.");
            error.printStackTrace();
            return null;
        }
        return cipherEncryptionHandler;
    }
}
