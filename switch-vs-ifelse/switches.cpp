extern "C" {
int fun(int i) {
    switch(i) {
        case 20:
            return 3;
        case 30:
            return 5;
        case 50:
            return 7;
        case 70:
            return 11;
        case 110:
            return 13;
        case 130:
            return 17;
        case 170:
            return 2;
        default:
            return 19;
    }
}

int fun2(int i) {
    if (i == 20) {
        return 3;
    } else if (i == 30) {
        return 5;
    } else if (i == 50) {
        return 7;
    } else if (i == 70) {
        return 11;
    } else if (i == 110) {
        return 13;
    } else if (i == 130) {
        return 17;
    } else if (i == 170) {
        return 2;
    } else {
        return 19;
    }
}
}