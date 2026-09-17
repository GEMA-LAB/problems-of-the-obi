"""Unit tests for src.core.http_client."""
import pytest
import responses
import requests
from pathlib import Path
from src.core.http_client import HttpClient
from src.core.config import DEFAULT_TIMEOUT


def test_http_client_get_success():
    client = HttpClient(timeout=DEFAULT_TIMEOUT)
    test_url = "https://example.com/test"

    with responses.RequestsMock() as rsps:
        rsps.add(responses.GET, test_url, body="OK", status=200)
        response = client.get(test_url)

        assert response is not None
        assert response.status_code == 200
        assert response.text == "OK"


def test_http_client_get_not_found():
    client = HttpClient(timeout=DEFAULT_TIMEOUT)
    test_url = "https://example.com/404"

    with responses.RequestsMock() as rsps:
        rsps.add(responses.GET, test_url, status=404)
        response = client.get(test_url)

        assert response is not None
        assert response.status_code == 404


def test_http_client_get_timeout_returns_none():
    client = HttpClient(timeout=1)
    test_url = "https://example.com/timeout"

    with responses.RequestsMock() as rsps:
        rsps.add(responses.GET, test_url, body=requests.exceptions.Timeout())
        response = client.get(test_url)

        assert response is None


def test_http_client_download_file_success(tmp_path):
    client = HttpClient(timeout=DEFAULT_TIMEOUT)
    test_url = "https://example.com/sample.pdf"
    dest = tmp_path / "subdir" / "sample.pdf"

    fake_pdf_content = b"%PDF-1.4 fake content"

    with responses.RequestsMock() as rsps:
        rsps.add(responses.GET, test_url, body=fake_pdf_content, status=200)
        success = client.download_file(test_url, dest)

        assert success is True
        assert dest.exists()
        assert dest.read_bytes() == fake_pdf_content


def test_http_client_download_file_failure(tmp_path):
    client = HttpClient(timeout=DEFAULT_TIMEOUT)
    test_url = "https://example.com/failed.pdf"
    dest = tmp_path / "failed.pdf"

    with responses.RequestsMock() as rsps:
        rsps.add(responses.GET, test_url, status=500)
        success = client.download_file(test_url, dest)

        assert success is False
        assert not dest.exists()
