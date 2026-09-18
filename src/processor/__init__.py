"""Processor domain package."""
from src.processor.matcher import ResourceMatcher, normalize_name
from src.processor.normalizer import TestCaseNormalizer
from src.processor.zip_extractor import ZipExtractor

__all__ = [
    "ResourceMatcher",
    "ZipExtractor",
    "TestCaseNormalizer",
    "normalize_name",
]


