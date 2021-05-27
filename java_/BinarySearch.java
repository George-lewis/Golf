package java_;

public class BinarySearch {
    private static <T extends Comparable<T>> int _binarySearch(T[] arr, int start, int end, T search) {
        int middle = (start + end) / 2;
        int cmp = search.compareTo(arr[middle]);
        if (cmp > 0) {
            return _binarySearch(arr, middle, end, search);
        } else if (cmp == 0) {
            return middle;
        } else /*if (cmp < 0)*/ {
            return _binarySearch(arr, start, middle, search);
        }
    }

    public static <T extends Comparable<T>> int binarySearch(T[] arr, T search) {
        return _binarySearch(arr, 0, arr.length - 1, search);
    }

    public static void main(String[] args) {
        {
            Integer[] arr = {0, 1, 2, 3, 4, 5, 6, 7, 8};
            int idx = binarySearch(arr, 3);
            assert idx == 3;
        }
        {
            Double[] arr = {0.1, 0.2, 0.3, 4.5, 7.7, 8.8, 8.89};
            int idx = binarySearch(arr, 7.7);
            assert idx == 4;
        }
    }
}