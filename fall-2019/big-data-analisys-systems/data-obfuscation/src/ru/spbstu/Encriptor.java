package ru.spbstu;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;

/**
 * Performcs encryption using AES algorithm.
 */
public class Encriptor {
    private static final String ENCRYPTION_ALGORITHM = "AES";
    /**
     * @param INITIALIZATION_VECTOR - initialization vector for CBC encryption.
     */
    private final String INITIALIZATION_VECTOR = "spbstu-data-analysis";
    private final String ENCRYPTION_KEY = "spbstu-encryption-key";


    public Encriptor() {}

    public String encryptStr(final String stringForObfuscation) {
        // NOTE: Specification of initialization vector.
        IvParameterSpec initVectorParameterSpec = new IvParameterSpec(this.INITIALIZATION_VECTOR.getBytes("UTF-8"));
        SecretKeySpec secretKeySpec = new SecretKeySpec(this.ENCRYPTION_KEY.getBytes("UTF-8"), Encriptor.ENCRYPTION_ALGORITHM);

        final String cipherAlgorithmTransformation = "AES/CBC/PKCS5PADDING";
        Cipher cipherEncriptionHandler = Cipher.getInstance(cipherAlgorithmTransformation);
        cipherEncriptionHandler.init(Cipher.ENCRYPT_MODE, secretKeySpec, initVectorParameterSpec);

        byte[] encryptedValue = cipherEncriptionHandler.doFinal(stringForObfuscation.getBytes());
        return Base64.getEncoder().encodeToString(encryptedValue);

    }
}
