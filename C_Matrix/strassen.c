//The strassen algorithm for matrix multiplication
//m1 = (a11 + a22) x (b11 + b22)
//m2 = (a12 + a22) x b11
//m3 = a11 * (b12 - b22)
//m4 = a22 * (B21 - b11)
//m5 = (a11 + a12) x b22
//m6 = (a21 - a11) x (b11 + b12)
//m7 = (a12 - a22) x (b21 + b22)


/*
    [c11 c12] = [   m1 + m4 -m5 + m7,   m3 + m5             ]
    [c21 c22]   [   m2 + m4         ,   m1 - m2 + m3 + m6   ]
*/