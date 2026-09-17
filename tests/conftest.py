"""Pytest shared fixtures."""
import pytest
from pathlib import Path


@pytest.fixture
def sample_obi_html():
    """Returns sample HTML content resembling an OBI past exams page."""
    return """
    <html>
      <body>
        <div class="content">
          <h2>Fase 1 - Programação</h2>
          <ul>
            <li><a href="caderno_pj.pdf">Caderno de Tarefas - Programação Júnior</a></li>
            <li><a href="caderno_p1.pdf">Caderno de Tarefas - Programação Nível 1</a></li>
            <li><a href="caderno_p2.pdf">Caderno de Tarefas - Programação Nível 2</a></li>
            <li><a href="solucao.zip">Gabarito com testes</a></li>
          </ul>
        </div>
      </body>
    </html>
    """
