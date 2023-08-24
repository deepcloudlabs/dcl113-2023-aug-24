numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

function* filtrele(dizi, test) { // HoF
    for (let element of dizi)
        if (test(element))
            yield element;
}

function* donustur(dizi, fun) { // HoF
    for (let element of dizi)
        yield fun(element);
}

function indirge(dizi, gun, init) { // HoF
    let acc = init;
    for (let element of dizi) {
        console.log("biriktir");
        acc = gun(acc, element);
    }
    return acc;
}

let is_even = x => x % 2 == 0;
let to_cube = u => u * u * u;
let add = (x, y) => x + y;
let sum = numbers.filter(is_even).map(to_cube).reduce(add, 0);

let sonuc =
    indirge(donustur(filtrele(numbers, x => {
        console.log("cift mi?");
        return x % 2 === 0;
    }), u => {
        console.log("kubunu al");
        return u ** 3;
    }), (x, y) => x + y, 0);
console.log(sonuc);
