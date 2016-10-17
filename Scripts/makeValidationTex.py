import os

tex = "\\documentclass{beamer}\n"
tex += "\\begin{document}\n\n"

runs = [275828,275829,275831,275832,275833,275834,275835,275836,275837,275838,
        275841,275846,275847,275886,275887,275890,275911,275912,275913,275918,
        275920,275921,275922,275923,275931,275963,276062,276063,276064,276071,
        276072,276092,276095,276097,276237,276242,276243,276244,276282,]


for run in runs:
    path = "20160708_Data_run-{0}_SingleMu".format(run)
    if not os.path.join(path): continue

    metPath = os.path.join(path,"Turnons","effs_SingleMu_caloMetBE_l1MetSeeds.pdf")
    httPath = os.path.join(path,"Turnons","effs_SingleMu_recoHtt_l1HttSeeds.pdf")
    jetBEPath = os.path.join(path,"TurnonsJets","effs_SingleMu_recoJetEt_l1JetEtSeeds_barrel-endcap.pdf")
    jetHFPath = os.path.join(path,"TurnonsJets","effs_SingleMu_recoJetEt_l1JetEtSeeds_hf.pdf")

    tex += "\\begin{frame}{Run "+str(run)+" - Jets}\n"
    tex += "Barrel+Endcap (left) and HF (right)\n"
    tex += "\\begin{figure}[!htbp]\n"
    tex += "\\centering\n"
    tex += "\\includegraphics[width=0.49\\textwidth]{"+jetBEPath+"}\n"
    tex += "\\includegraphics[width=0.49\\textwidth]{"+jetHFPath+"}\n"
    tex += "\\end{figure}\n"
    tex += "\\end{frame}\n\n"
    
    tex += "\\begin{frame}{Run "+str(run)+" - Sums}\n"
    tex += "MET (left) and HTT (right)\n"
    tex += "\\begin{figure}[!htbp]\n"
    tex += "\\centering\n"
    tex += "\\includegraphics[width=0.49\\textwidth]{"+metPath+"}\n"
    tex += "\\includegraphics[width=0.49\\textwidth]{"+httPath+"}\n"
    tex += "\\end{figure}\n"
    tex += "\\end{frame}\n\n"

tex += "\\end{document}"

print tex
