"""Pipeline de Automacao e Catalogacao da OBI."""
import argparse
from pathlib import Path
from dotenv import load_dotenv

from src.core.config import (
    DEFAULT_CODIGO_DIR,
    DEFAULT_GABARITOS_DIR,
    DEFAULT_OUTPUT_DIR,
    DEFAULT_PYTHON_DATASET_DIR,
    OrganizeConfig,
)
from src.crawler.cadernos_downloader import CadernosDownloader
from src.crawler.codigos_downloader import CodigosDownloader
from src.crawler.gabaritos_downloader import GabaritosDownloader
from src.extractor import OpenAiExtractor
from src.processor import PythonDatasetBuilder, QuestionsOrganizer

# Carregar variáveis de ambiente
load_dotenv()


def main():
    parser = argparse.ArgumentParser(description="Pipeline de Automação e Catalogação da OBI")
    parser.add_argument(
        "--step",
        choices=[
            "download-cadernos",
            "download-codigos",
            "download-gabaritos",
            "extract-questions",
            "organize-questions",
            "organize-testcases",
            "clean-testcases",
            "export-python-dataset",
            "all",
        ],
        default="all",
        help="Etapa específica a ser executada (padrão: all)"
    )
    parser.add_argument("--ano", type=int, default=None, help="Filtrar por ano específico (ex: 2024)")
    parser.add_argument("--nivel", type=str, default=None, help="Filtrar por nível específico (ex: pj, p1, p2, senior)")
    parser.add_argument("--force", action="store_true", help="Forçar download mesmo se o arquivo já existir")

    args = parser.parse_args()

    print("\nINICIANDO PIPELINE DE AUTOMACAO DA OBI\n")

    # Passo 1: Baixar PDFs (via CadernosDownloader modular)
    if args.step in ["download-cadernos", "all"]:
        print(f"\n{'='*40}")
        print("1. DOWNLOAD DOS CADERNOS (PDFs)")
        print(f"{'='*40}")
        downloader = CadernosDownloader()
        stats = downloader.crawl_and_download(
            ano_filtro=args.ano,
            nivel_filtro=args.nivel,
            force=args.force
        )
        print(f"Estatisticas dos Cadernos: {stats}")

        if args.step == "download-cadernos":
            print("\nETAPA DOWNLOAD-CADERNOS FINALIZADA COM SUCESSO.")
            return

    # Passo 1.5: Baixar Codigos e Solucoes Oficiais (via CodigosDownloader modular)
    if args.step in ["download-codigos", "all"]:
        print(f"\n{'='*40}")
        print("1.5. DOWNLOAD DOS CODIGOS DE SOLUCAO")
        print(f"{'='*40}")
        codigos_downloader = CodigosDownloader()
        stats_codigos = codigos_downloader.crawl_and_download(
            ano_filtro=args.ano,
            nivel_filtro=args.nivel,
            force=args.force
        )
        print(f"Estatisticas dos Codigos: {stats_codigos}")

        if args.step == "download-codigos":
            print("\nETAPA DOWNLOAD-CODIGOS FINALIZADA COM SUCESSO.")
            return

    # Passo 2: Mandar para LLM (via OpenAiExtractor modular)
    if args.step in ["extract-questions", "all"]:
        print(f"\n{'='*40}")
        print("2. EXTRACAO DE DADOS (API OPENAI)")
        print(f"{'='*40}")
        path_data = Path("cadernos") if Path("cadernos").exists() else Path("backup")

        # Filtros por ano e nivel se informados
        if args.ano and args.nivel:
            busca_path = path_data / str(args.ano) / args.nivel.lower()
            pdfs_path = list(busca_path.rglob("*.pdf")) if busca_path.exists() else []
        elif args.ano:
            busca_path = path_data / str(args.ano)
            pdfs_path = list(busca_path.rglob("*.pdf")) if busca_path.exists() else []
        else:
            pdfs_path = list(path_data.rglob("*.pdf"))
            if args.nivel:
                pdfs_path = [p for p in pdfs_path if args.nivel.lower() in [part.lower() for part in p.parts]]

        extractor = OpenAiExtractor()
        max_tentativas = 3
        tentativa = 0
        while pdfs_path and tentativa < max_tentativas:
            tentativa += 1
            print(f"Tentativa {tentativa} de extracao ({len(pdfs_path)} arquivos)...")
            _, pdfs_path = extractor.process_cadernos(pdfs_path)

        if args.step == "extract-questions":
            print("\nETAPA EXTRACT-QUESTIONS FINALIZADA COM SUCESSO.")
            return

    # Passo 3: Baixar ZIPs de gabaritos (via GabaritosDownloader modular)
    if args.step in ["download-gabaritos", "all"]:
        print(f"\n{'='*40}")
        print("3. DOWNLOAD DOS GABARITOS (ZIPs)")
        print(f"{'='*40}")
        gabaritos_downloader = GabaritosDownloader()
        stats_gabaritos = gabaritos_downloader.crawl_and_download(
            ano_filtro=args.ano,
            nivel_filtro=args.nivel,
            force=args.force
        )
        print(f"Estatisticas dos Gabaritos: {stats_gabaritos}")

        if args.step == "download-gabaritos":
            print("\nETAPA DOWNLOAD-GABARITOS FINALIZADA COM SUCESSO.")
            return

    # Passo 4: Organizar questoes, casos de teste e solucoes (via QuestionsOrganizer modular)
    if args.step in ["organize-questions", "organize-testcases", "clean-testcases", "all"]:
        print(f"\n{'='*40}")
        print("4. ORGANIZACAO DE QUESTOES, GABARITOS E SOLUCOES")
        print(f"{'='*40}")
        output_base = DEFAULT_OUTPUT_DIR if DEFAULT_OUTPUT_DIR.exists() else (
            Path("output_question_obi") if Path("output_question_obi").exists() else Path("output")
        )
        organize_config = OrganizeConfig(
            pasta_output=output_base,
            pasta_gabaritos=DEFAULT_GABARITOS_DIR,
            pasta_codigo=DEFAULT_CODIGO_DIR,
            force=args.force,
        )
        organizer = QuestionsOrganizer()
        stats_org = organizer.organize_all(
            config=organize_config,
            ano_filtro=args.ano,
            nivel_filtro=args.nivel,
        )
        print(f"Estatisticas da Organizacao: {stats_org}")

        if args.step in ["organize-questions", "organize-testcases", "clean-testcases"]:
            print("\nETAPA ORGANIZE-QUESTIONS FINALIZADA COM SUCESSO.")
            return

    # Passo 5: Exportar dataset com solucoes em Python (via PythonDatasetBuilder modular)
    if args.step in ["export-python-dataset"]:
        print(f"\n{'='*40}")
        print("5. EXPORTACAO DO DATASET OBI PYTHON")
        print(f"{'='*40}")
        source_dir = DEFAULT_OUTPUT_DIR if DEFAULT_OUTPUT_DIR.exists() else Path("output")
        builder = PythonDatasetBuilder()
        stats_dataset = builder.build_dataset(
            source_dir=source_dir,
            target_dir=DEFAULT_PYTHON_DATASET_DIR,
            ano_filtro=args.ano,
            nivel_filtro=args.nivel,
            force=args.force,
        )
        print(f"Estatisticas da Exportacao Python: {stats_dataset}")
        print("\nETAPA EXPORT-PYTHON-DATASET FINALIZADA COM SUCESSO.")
        return

    print("\nPIPELINE COMPLETA FINALIZADA COM SUCESSO.")


if __name__ == "__main__":
    main()
