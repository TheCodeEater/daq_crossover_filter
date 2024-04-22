Double_t seno(double* x, double* par) {
    Double_t sin = std::sin(TMath::TwoPi() * par[0] * x[0] + par[1]); 
    return sin;
}

Double_t calcNoise(Double_t value) {
    // TODO Da implementare
}

void generateData(Int_t nPoints = 100; Double_t freq = 158.5e3, Double_t phase = 0) {
    gRandom->setSeed();

    if (phase == 0) {
        pahse = gRandom->Uniform(0, TMath::TwoPi());
    }

    auto gen = new TF1("gen", seno, -1e23, 1e23, 2);
    // f1->SetNpx(1000);
    gen->SetParameters(freq, phase);
    gen->SetParNames("frequency", "phase");

    for (Int_t i = 0; i < nPoints; i++) {
        // Leggo a 500kHz
        Double_t t = i * 1 / 5e3;
        Double_t V = gen->Eval(t);
        // Aggiungo l'errore di misura
        V = V + calcNoise(V);
    }
}