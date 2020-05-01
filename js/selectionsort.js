//////////////////////////////////
// Selection sort in JavaScript //
//////////////////////////////////
function selection_sort(array) {
    let idx = 0
    for (let i = 0; i < array.length; i++) {
        idx = i
        for (let j = i+1; j < array.length; j++) {
            if (array[j] < array[idx]) {
                x = array[idx]
                array[idx] = array[j]
                array[j] = x
            }
        }
    }
}

a = [ 9, 8, 5, 3, 5 ]
console.log(a)
selection_sort(a)
console.log(a)