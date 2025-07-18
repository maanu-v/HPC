import java.util.Random;
import java.util.concurrent.TimeUnit;

public class MatrixMultiplier {

    private final int n; // Matrix dimension
    private final double[][] A;
    private final double[][] B;
    private final double[][] C;

    /**
     * Constructor to initialize matrices of a given size.
     * 
     * @param size The dimension (n) of the square matrices.
     */
    public MatrixMultiplier(int size) {
        if (size <= 0) {
            throw new IllegalArgumentException("Matrix size must be positive.");
        }
        this.n = size;
        this.A = new double[n][n];
        this.B = new double[n][n];
        this.C = new double[n][n];
    }

    /**
     * Fills matrices A and B with random values.
     */
    public void initializeMatrices() {
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand.nextDouble();
                B[i][j] = rand.nextDouble();
                // C is already initialized to 0.0 by default in Java
            }
        }
    }

    /**
     * Performs matrix multiplication C = A * B using an optimized loop order.
     */
    public void multiply() {
        // Using ikj loop order for better cache performance.
        // A[i][k] is accessed sequentially.
        // B[k][j] is accessed across rows, but this is better than the original.
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                // Store A[i][k] in a local variable for a small additional optimization
                final double a_ik = A[i][k];
                for (int j = 0; j < n; j++) {
                    C[i][j] += a_ik * B[k][j];
                }
            }
        }
    }

    public static void main(String[] args) {
        int matrixSize = 256;
        System.out.println("Performing matrix multiplication for size " + matrixSize + "x" + matrixSize);

        MatrixMultiplier mm = new MatrixMultiplier(matrixSize);

        System.out.println("Initializing matrices with random values...");
        mm.initializeMatrices();

        System.out.println("Performing multiplication...");
        long startTime = System.nanoTime();

        mm.multiply();

        long endTime = System.nanoTime();
        long durationNanos = endTime - startTime;
        double durationSeconds = TimeUnit.NANOSECONDS.toMillis(durationNanos) / 1000.0;

        System.out.printf("Multiplication completed in: %.4f seconds%n", durationSeconds);
    }
}